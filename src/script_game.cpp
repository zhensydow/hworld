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
/** @file script_game.cpp
    @brief Game script library.
    @author Luis Cabellos
    @date 2014-01-22
*/
//------------------------------------------------------------------------------
#include "script.hpp"
#include "engine.hpp"
#include "gfx.hpp"

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
static int game_setSunDir( lua_State *ls ){
    auto x = luaL_checknumber( ls, 1 );
    auto y = luaL_checknumber( ls, 2 );
    auto z = luaL_checknumber( ls, 3 );
    auto & engine = Engine::instance();
    auto & gfx = engine.getGfx();

    gfx.setSunDir( glm::vec3( x, y, z ) );

    return 0;
}

//------------------------------------------------------------------------------
/** List of functions of game lua library.
*/
static const luaL_Reg gamelib[] = {
    {"setSunDir", game_setSunDir},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openGame( lua_State * lua ){
    // set engine functions
    luaL_register( lua, "game", gamelib );
    // removes table
    lua_pop( lua, 1 );
}

//------------------------------------------------------------------------------
