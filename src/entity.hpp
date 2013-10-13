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
    template<typename T> T & getComponent( ComponentType ct );
    void insertComponent( std::shared_ptr<Component> c );

private:
    std::unordered_map< ComponentType, std::shared_ptr<Component>, ComponentType_hash > m_components;
};

//------------------------------------------------------------------------------
template<typename T>
T & Entity::getComponent( ComponentType ct ){
    auto it = m_components.find( ct );

    if( it != m_components.end() ){
        return *std::dynamic_pointer_cast<T>(it->second);
    }

    std::terminate();
}

//------------------------------------------------------------------------------
#endif//ENTITY_HPP_

//------------------------------------------------------------------------------
