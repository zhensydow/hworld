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
/** @file script_terminal.cpp
    @brief Terminal script library.
    @author Luis Cabellos
    @date 2014-01-23
*/
//------------------------------------------------------------------------------
#include "script.hpp"
#include "engine.hpp"
#include "terminal.hpp"

//------------------------------------------------------------------------------
int terminal_newLine( lua_State *lua ){
    std::string val = luaL_checkstring( lua, 1 );

    auto & engine = Engine::instance();
    auto & terminal = engine.getTerminal();
    
    terminal.newLine( val );

    return 0;
}

//------------------------------------------------------------------------------
void openTerminal( lua_State * lua ){
    // set input
    lua_newtable( lua );                            // 1
    lua_pushstring( lua, "newLine");                // 2
    lua_pushcfunction( lua, terminal_newLine );     // 3
    lua_settable( lua, -3 );                        // 1

    lua_setglobal( lua, "terminal" );               // 0
}

//------------------------------------------------------------------------------
