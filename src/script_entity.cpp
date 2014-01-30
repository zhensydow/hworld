/**
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
**/
/** @file script_entity.cpp
    @brief Entity library script.
    @author Luis Cabellos
    @date 2014-01-23
*/
//------------------------------------------------------------------------------
#include "script.hpp"
#include <string>
#include <iostream>
#include <memory>
#include "entity.hpp"
#include "component.hpp"

//------------------------------------------------------------------------------
int component_index( lua_State *lua ){
    std::string name = luaL_checkstring( lua, 2 );
    lua_pushstring( lua, "_comp" );
    lua_rawget( lua, -3 );
    auto component = static_cast<Component*>( lua_touserdata( lua, -1 ) );
    if( component ){
        auto function = component->getFunction( name );
        if( function ){
            lua_pushcfunction( lua, function );
            return 1;
        }
    }
    return 0;
}

//------------------------------------------------------------------------------
int component_newindex( lua_State *lua ){
    std::string name = luaL_checkstring( lua, 2 );
    std::cout << "NEW COMP INDEX " << name << std::endl;
    return 0;
}

//------------------------------------------------------------------------------
void lua_pushComponent( lua_State * lua, std::shared_ptr<Component> & comp ){
    lua_newtable( lua );                             // 1
    lua_pushstring( lua, "_comp" );                  // 2
    lua_pushlightuserdata( lua, comp.get() );        // 3
    lua_settable( lua, -3 );                         // 1
    lua_newtable( lua );                             // 2
    lua_pushstring( lua, "__newindex");              // 3
    lua_pushcfunction( lua, component_newindex );    // 4
    lua_settable( lua, -3 );                         // 2
    lua_pushstring( lua, "__index");                 // 3
    lua_pushcfunction( lua, component_index );       // 4
    lua_settable( lua, -3 );                         // 2
    lua_setmetatable( lua, -2 );                     // 1
}

//------------------------------------------------------------------------------
int entity_index( lua_State *lua ){
    std::string name = luaL_checkstring( lua, 2 );
    lua_pushstring( lua, "_ent" );
    lua_rawget( lua, -3 );
    auto entity = static_cast<Entity*>( lua_touserdata( lua, -1 ) );
    if( entity ){
        auto tt = getComponentType( name );
        auto comp = entity->getComponent( tt );
        if( comp ){
            lua_pushComponent( lua, comp );
            return 1;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
int entity_newindex( lua_State *lua ){
    std::string name = luaL_checkstring( lua, 2 );
    std::cout << "NEW INDEX " << name << std::endl;
    return 0;
}

//------------------------------------------------------------------------------
void lua_pushEntity( lua_State * lua, Entity & entity ){
    lua_newtable( lua );                             // 1
    lua_pushstring( lua, "_ent" );                   // 2
    lua_pushlightuserdata( lua, &entity );           // 3
    lua_settable( lua, -3 );                         // 1
    lua_newtable( lua );                             // 2
    lua_pushstring( lua, "__newindex");              // 3
    lua_pushcfunction( lua, entity_newindex );       // 4
    lua_settable( lua, -3 );                         // 2
    lua_pushstring( lua, "__index");                 // 3
    lua_pushcfunction( lua, entity_index );          // 4
    lua_settable( lua, -3 );                         // 2
    lua_setmetatable( lua, -2 );                     // 1
}

//------------------------------------------------------------------------------
Entity * lua_checkEntity( lua_State * lua, int index ){
    lua_pushvalue( lua, index );    // 1
    lua_pushstring( lua, "_ent" );  // 2
    lua_rawget( lua, -2 );          // 2
    auto entity = static_cast<Entity*>( lua_touserdata( lua, -1 ) );
    lua_pop( lua, 2 );
    if( not entity ){
        luaL_error( lua, "invalid entity" );
    }

    return entity;
}

//------------------------------------------------------------------------------
