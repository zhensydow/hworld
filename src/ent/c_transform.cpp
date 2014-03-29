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
/** @file c_transform.cpp
    @brief Tranform Component Definition.
    @author Luis Cabellos
    @date 2013-10-20
*/
//------------------------------------------------------------------------------
#include "c_transform.hpp"

//------------------------------------------------------------------------------
constexpr ComponentType CTransform::type;

//------------------------------------------------------------------------------
int ctransform_setPosition( lua_State * lua ){
    int n = lua_gettop( lua );
    if( n != 4 ){
        lua_pushstring( lua, "incorrect number of arguments" );
        lua_error( lua );
        return 0;
    }

    auto x = luaL_checknumber( lua, 2 );
    auto y = luaL_checknumber( lua, 3 );
    auto z = luaL_checknumber( lua, 4 );

    lua_pushstring( lua, "_comp" );
    lua_rawget( lua, -5 );
    auto component = static_cast<CTransform*>( lua_touserdata( lua, -1 ) );
    if( component ){
        component->setPosition( glm::vec3( x, y, z ) );
    }

    lua_pop( lua, 1 );

    return 0;
}

//------------------------------------------------------------------------------
Component::ScriptTable CTransform::s_transformTable = {
    { "setPosition", ctransform_setPosition },
};

//------------------------------------------------------------------------------
CTransform::CTransform( Entity & e ) : Component( e ){
    registerScriptTable( &s_transformTable );
}

//------------------------------------------------------------------------------
