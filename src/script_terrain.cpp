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
/** @file script_terrain.cpp
    @brief Script functions for terrain.
    @author Luis Cabellos
    @date 2014-02-16
*/
//------------------------------------------------------------------------------
#include "script.hpp"

//------------------------------------------------------------------------------
/** List of functions of terrain lua library.
*/
const luaL_Reg terrainlib[] = {
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openTerrain( lua_State * lua ){
    // set terrain functions
    luaL_register( lua, "terrain", terrainlib );
    // removes table
    lua_pop( lua, 1 );
}

//------------------------------------------------------------------------------
