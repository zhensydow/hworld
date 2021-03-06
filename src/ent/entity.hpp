/*------------------------------------------------------------------------------
    Copyright 2014, HexWorld Authors.

    This file is part of HexWorld.

    HexWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HexWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HexWorld.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------*/
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
#include <cassert>
#include "components.hpp"
#include "types.hpp"

//------------------------------------------------------------------------------
class Component;

//------------------------------------------------------------------------------
class Entity final {
public:
    static EntityID nextID();

    Entity( EntityID id );
    bool hasComponent( ComponentType ct ) const;
    template<typename T> std::shared_ptr<T> getComponent();
    template<typename T=Component> std::shared_ptr<T> getComponent( ComponentType type );
    void insertComponent( std::shared_ptr<Component> c );

    EntityID id() const;

    void printDebug() const;

private:
    static EntityID s_lastID;

    EntityID m_id;

    std::unordered_map< ComponentType, std::shared_ptr<Component>, ComponentType_hash > m_components;
};

//------------------------------------------------------------------------------
inline
EntityID Entity::nextID(){
    return ++s_lastID;
}

//------------------------------------------------------------------------------
inline
Entity::Entity( EntityID id ) : m_id(id) {
    assert( m_id != ENTITY_NULL_IDX && "Bad Entity ID" );
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
inline
EntityID Entity::id() const{
    return m_id;
}

//------------------------------------------------------------------------------
#endif//ENTITY_HPP_

//------------------------------------------------------------------------------
