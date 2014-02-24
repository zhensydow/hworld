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
/** @file script_engine.cpp
    @brief Engine script functions.
    @author Luis Cabellos
    @date 2014-01-20
*/
//------------------------------------------------------------------------------
#include "engine.hpp"
#include "lua.hpp"
#include "entity.hpp"
#include "script.hpp"
#include "filedata.hpp"
#include "gfx.hpp"
#include "terminal.hpp"

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
int engine_newState( lua_State *ls ){
    auto str = luaL_checkstring( ls, 1 );
    auto & engine = Engine::instance();
    auto state = engine.makeGameState( str );
    engine.setState( std::move(state) );

    return 0;
}

//------------------------------------------------------------------------------
int engine_newEntity( lua_State *ls ){
    auto str = std::string( luaL_checkstring( ls, 1 ) );

    auto n = str.rfind( ".json" );
    if( n == std::string::npos ){
        str += ".json";
    }else{
        if( str.substr(n) != ".json" ){
            str += ".json";
        }
    }

    auto & engine = Engine::instance();
    auto id = Entity::nextID();
    auto entity = makeEntity( id, engine.getDataFilename( str ) );
    if( entity ){
        engine.addEntity( entity );
        lua_pushEntity( ls, *entity );

        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
int engine_setCamera( lua_State *ls ){
    auto ent = lua_checkEntity( ls, 1 );
    if( ent ){
        auto & engine = Engine::instance();
        auto entity = engine.getEntity( ent->id() );
        if( entity ){
            engine.setCamera( entity );
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
static int engine_hasCamera( lua_State *ls ){
    auto & engine = Engine::instance();
    lua_pushboolean( ls, engine.hasCamera() );
    return 1;
}

//------------------------------------------------------------------------------
int engine_saveWorld( lua_State *ls ){
    auto str = luaL_checkstring( ls, 1 );
    auto & engine = Engine::instance();
    auto & world = engine.getWorld();
    auto & terminal = engine.getTerminal();
    terminal.newLine( "Saving..." );
    saveWorld( world, str );
    return 0;
}

//------------------------------------------------------------------------------
int engine_enableRenderEffects( lua_State *ls ){
    auto v = lua_toboolean( ls, 1 ) == 1;
    auto & engine = Engine::instance();
    auto & gfx = engine.getGfx();
    gfx.enableRenderEffects( v );
    return 0;
}

//------------------------------------------------------------------------------
/** List of functions of engine lua library.
*/
const luaL_Reg enginelib[] = {
    {"newState",  engine_newState},
    {"newEntity", engine_newEntity},
    {"hasCamera", engine_hasCamera},
    {"setCamera", engine_setCamera},
    {"saveWorld", engine_saveWorld},
    {"enableRenderEffects", engine_enableRenderEffects},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openEngine( lua_State * lua ){
    // set engine functions
    luaL_register( lua, "engine", enginelib );
    // removes table
    lua_pop( lua, 1 );
}

//------------------------------------------------------------------------------
