/** @file entity.hpp
    @brief Entity Class Declaration.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#ifndef ENTITY_HPP_
#define ENTITY_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include <memory>
#include "components.hpp"
#include <cassert>

//------------------------------------------------------------------------------
class Component;

//------------------------------------------------------------------------------
constexpr unsigned int ENTITY_NULL_ID {0};

//------------------------------------------------------------------------------
class Entity final {
public:
    static unsigned int nextID();

    Entity( unsigned int id );
    bool hasComponent( ComponentType ct ) const;
    template<typename T> std::shared_ptr<T> getComponent();
    template<typename T=Component> std::shared_ptr<T> getComponent( ComponentType type );
    void insertComponent( std::shared_ptr<Component> c );

    void printDebug() const;

private:
    static unsigned int s_lastID;

    unsigned int m_id;

    std::unordered_map< ComponentType, std::shared_ptr<Component>, ComponentType_hash > m_components;
};

//------------------------------------------------------------------------------
inline
unsigned int Entity::nextID(){
    return ++s_lastID;
}

//------------------------------------------------------------------------------
inline
Entity::Entity( unsigned int id ) : m_id(id) {
    assert( m_id != ENTITY_NULL_ID && "Bad Entity ID" );
}

//------------------------------------------------------------------------------
template<typename T>
std::shared_ptr<T> Entity::getComponent(){
    auto it = m_components.find( T::type );

    if( it != m_components.end() ){
        return std::static_pointer_cast<T>(it->second);
    }

    return nullptr;
}

//------------------------------------------------------------------------------
template<typename T>
std::shared_ptr<T> Entity::getComponent( ComponentType type ){
    auto it = m_components.find( type );

    if( it != m_components.end() ){
        return std::static_pointer_cast<T>(it->second);
    }

    return nullptr;
}

//------------------------------------------------------------------------------
template<typename C, typename... Args>
std::shared_ptr<C> newComponent( Entity & entity, Args&&... args ){
    auto comp = std::make_shared<C>( entity, std::forward<Args>(args)... );
    entity.insertComponent( comp );
    return comp;
}

//------------------------------------------------------------------------------
template<typename C, typename... Args>
std::shared_ptr<C> getMakeComponent( Entity & entity, Args&&... args ){
    auto comp = entity.getComponent<C>();
    if( not comp ){
        comp = std::make_shared<C>( entity, std::forward<Args>(args)... );
        entity.insertComponent( comp );
    }
    return comp;
}

//------------------------------------------------------------------------------
#endif//ENTITY_HPP_

//------------------------------------------------------------------------------
