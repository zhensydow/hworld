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

//------------------------------------------------------------------------------
class Component;

//------------------------------------------------------------------------------
class Entity final {
public:
    bool hasComponent( ComponentType ct ) const;
    template<typename T> std::shared_ptr<T> getComponent();
    template<typename T=Component> std::shared_ptr<T> getComponent( ComponentType type );
    void insertComponent( std::shared_ptr<Component> c );

private:
    std::unordered_map< ComponentType, std::shared_ptr<Component>, ComponentType_hash > m_components;
};

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
#endif//ENTITY_HPP_

//------------------------------------------------------------------------------
