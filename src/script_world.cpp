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
/** @file script_world.cpp
    @brief Script functions for the world.
    @author Luis Cabellos
    @date 2014-02-16
*/
//------------------------------------------------------------------------------
#include "script.hpp"
#include "debug.hpp"
#include "engine.hpp"
#include "world.hpp"
#include "entity.hpp"

//------------------------------------------------------------------------------
int world_terrainFocus( lua_State *ls ){
    auto & engine = Engine::instance();

    lua_pushinteger( ls, engine.terrainFocus() ); // 1

    return 1;
}

//------------------------------------------------------------------------------
int world_setTerrainFocus( lua_State *ls ){
    auto chunk_id = luaL_checkint( ls, 1 );

    logI( "Setting Terrain Focus ", chunk_id );
    auto & engine = Engine::instance();
    engine.setTerrainFocus( chunk_id );

    return 0;
}

//------------------------------------------------------------------------------
int world_hasEntity( lua_State *ls ){
    auto chunk_id = luaL_checkint( ls, 1 );
    auto tile_pos = luaL_checkint( ls, 2 );

    auto & engine = Engine::instance();
    auto & world = engine.getWorld();

    lua_pushboolean( ls, world.hasEntity( chunk_id, tile_pos ) ? 1 : 0 );

    return 1;
}

//------------------------------------------------------------------------------
int world_addEntity( lua_State *ls ){
    auto chunk_id = luaL_checkint( ls, 1 );
    auto tile_pos = luaL_checkint( ls, 2 );
    auto ent = lua_checkEntity( ls, 3 );
    if( ent ){
        auto & engine = Engine::instance();
        engine.addTerrainEntity( chunk_id, tile_pos, ent->id() );
    }

    return 0;
}

//------------------------------------------------------------------------------
int world_hasChunk( lua_State *ls ){
    auto chunk_id = luaL_checkint( ls, 1 );

    auto & engine = Engine::instance();
    auto & world = engine.getWorld();

    lua_pushboolean( ls, world.hasChunk( chunk_id ) ? 1 : 0 );

    return 1;
}

//------------------------------------------------------------------------------
/** List of functions of world lua library.
*/
const luaL_Reg terrainlib[] = {
    {"terrainFocus", world_terrainFocus},
    {"setTerrainFocus", world_setTerrainFocus},
    {"hasEntity", world_hasEntity},
    {"addEntity", world_addEntity},
    {"hasChunk", world_hasChunk},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openWorld( lua_State * lua ){
    // set world functions
    luaL_register( lua, "world", terrainlib );
    // removes table
    lua_pop( lua, 1 );
}

//------------------------------------------------------------------------------
