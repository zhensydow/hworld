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
/** @file c_script.cpp
    @brief SCript Component Definition.
    @author Luis Cabellos
    @date 2013-10-22
*/
//------------------------------------------------------------------------------
#include "c_script.hpp"
#include <iostream>
#include <boost/filesystem.hpp>
#include "util.hpp"
#include "script.hpp"

//------------------------------------------------------------------------------
using namespace boost::filesystem;

//------------------------------------------------------------------------------
constexpr ComponentType CScript::type;

//------------------------------------------------------------------------------
CScript::CScript( Entity & e ) : Component( e ) {
    //empty
}

//------------------------------------------------------------------------------
CScript::~CScript(){
    if( m_lua ){
        lua_close( m_lua );
    }
}

//------------------------------------------------------------------------------
void CScript::load( const std::string & filename ){
    if( !is_regular_file(filename) ){
        std::cout << "Not file '" << filename << "'" << std::endl;
    }

    // Lua Initialization
    m_lua = luaL_newstate();
    if( !m_lua ){
        std::cout << "Can't create Lua State" << std::endl;
    }

    lua_gc( m_lua, LUA_GCSTOP, 0 );
    luaL_openlibs( m_lua );
    openInput( m_lua );
    openTerminal( m_lua );
    openGLM( m_lua );
    // set entity
    lua_pushEntity( m_lua, getEntity() );              // 1
    lua_setfield( m_lua, LUA_GLOBALSINDEX, "entity" ); // 0

    lua_gc( m_lua, LUA_GCRESTART, 0 );

    // execute class file
    auto ret = luaL_dofile( m_lua, filename.c_str() );
    if( !checkLuaReturn( m_lua, ret ) ){
        m_lua = nullptr;
    }
}

//------------------------------------------------------------------------------
void CScript::update( double d ){
    if( m_lua ){
        lua_getfield( m_lua, LUA_GLOBALSINDEX, "onUpdate" );     // 1
        if( lua_isfunction( m_lua, -1 ) ){
            lua_pushnumber( m_lua, d );                          // 2
            auto ret = lua_pcall( m_lua, 1, 0, 0 );              // 0
            checkLuaReturn( m_lua, ret );
        }else{
            lua_pop( m_lua, 1 );                                 // 0
        }
    }
}

//------------------------------------------------------------------------------
