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
/** @file component.hpp
    @brief Component Base Class Declaration.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include "lua.hpp"
#include "entity.hpp"

//------------------------------------------------------------------------------
class Component {
public:
    Component( Entity & e ) noexcept;
    virtual ~Component();

    virtual ComponentType getType() const = 0;

    Entity & getEntity();

    lua_CFunction getFunction( const std::string & name ) const;

protected:
    using ScriptTable = std::unordered_map< std::string, lua_CFunction>;
    void registerScriptTable( ScriptTable * table );

private:
    ScriptTable * m_scriptTable = nullptr;

    Entity & m_entity;
};

//------------------------------------------------------------------------------
inline
Entity & Component::getEntity(){
    return m_entity;
}

//------------------------------------------------------------------------------
inline
bool hasComponent( Component & c, ComponentType ct ){
    return c.getEntity().hasComponent( ct );
}

//------------------------------------------------------------------------------
inline
void Component::registerScriptTable( Component::ScriptTable * table ){
    m_scriptTable = table;
}

//------------------------------------------------------------------------------
template<typename T>
inline
std::shared_ptr<T> getComponent( Component & c ){
    return c.getEntity().getComponent<T>();
}

//------------------------------------------------------------------------------
#endif//COMPONENT_HPP_

//------------------------------------------------------------------------------
