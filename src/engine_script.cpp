/** @file engine_script.cpp
    @brief Engine script functions.
    @author Luis Cabellos
    @date 2014-01-20
*/
//------------------------------------------------------------------------------
#include "engine.hpp"
#include "lua.hpp"
#include "script.hpp"
#include "filedata.hpp"

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
    auto entity = makeEntity( engine.getDataFilename( str ) );
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
        auto entity = engine.getEntity( ent );
        if( entity ){
            engine.setCamera( entity );
        }
    }

    return 0;
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
/** List of functions of AgentClass lua library for Agent files.
*/
const luaL_Reg enginelib[] = {
    {"newState",  engine_newState},
    {"newEntity", engine_newEntity},
    {"setCamera", engine_setCamera},
    {"saveWorld", engine_saveWorld},
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
