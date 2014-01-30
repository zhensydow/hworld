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
/** @file script.hpp
    @brief Script open functions.
    @author Luis Cabellos
    @date 2014-01-23
*/
//------------------------------------------------------------------------------
#ifndef SCRIPT_HPP_
#define SCRIPT_HPP_

//------------------------------------------------------------------------------
#include "lua.hpp"

//------------------------------------------------------------------------------
class Entity;

//------------------------------------------------------------------------------
void openEngine( lua_State * lua );
void openGame( lua_State * lua );
void openInput( lua_State * lua );
void openTerminal( lua_State * lua );
void openGLM( lua_State * lua );
void lua_pushEntity( lua_State * lua, Entity & entity );
Entity * lua_checkEntity( lua_State * lua, int index );

//------------------------------------------------------------------------------
#endif//SCRIPT_HPP_

//------------------------------------------------------------------------------
