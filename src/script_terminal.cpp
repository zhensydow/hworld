//------------------------------------------------------------------------------
#include "script.hpp"
#include "engine.hpp"

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
