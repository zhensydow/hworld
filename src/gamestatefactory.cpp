/** @file gamestatefactory.cpp
    @brief GameStateFactory definitions.
    @author Luis Cabellos
    @date 2013-09-29
*/
//------------------------------------------------------------------------------
#include "gamestatefactory.hpp"
#include "lua.hpp"
#include "gs_lua.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
using namespace std;
using namespace boost::filesystem;

//------------------------------------------------------------------------------
shared_ptr<GameState> GameStateFactory::makeGSLua( const string & name ) const{
    path filename = path(m_datadir) /= (name + ".lua");

    if( !is_regular_file( filename ) ){
        cout << "Not file for class '" <<  name << "'" << endl;
        return nullptr;
    }

    // Lua Initialization
    auto ls = luaL_newstate();
    if( !ls ){
        cout << "Can't create Lua State" << endl;
        return nullptr;
    }

    lua_gc( ls, LUA_GCSTOP, 0 );
    luaL_openlibs( ls );
    lua_gc( ls, LUA_GCRESTART, 0 );

    // create Lua Game State
    auto state = make_shared<GSLua>( ls );
    if( !state ){
        lua_close( ls );
        cout << "Can't create agent class '" << name << "' instance" << endl;
        return nullptr;
    }

    // execute class file
    auto ret = luaL_dofile( ls, filename.c_str() );
    if( !checkLuaReturn( ls, ret ) ){
        return nullptr;
    }

    return state;
}

//------------------------------------------------------------------------------
