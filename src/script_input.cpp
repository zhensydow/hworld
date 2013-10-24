//------------------------------------------------------------------------------
#include "script.hpp"
#include <SFML/Graphics.hpp>

//------------------------------------------------------------------------------
int isKeyPressed( lua_State *lua ){
    auto val = luaL_checkint( lua, 1 );
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(val));
}

//------------------------------------------------------------------------------
void openInput( lua_State * lua ){
    // set input
    lua_newtable( lua );                            // 1
    lua_pushstring( lua, "isKeyPressed");           // 2
    lua_pushcfunction( lua, isKeyPressed );         // 3
    lua_settable( lua, -3 );                        // 1
    lua_pushstring( lua, "K" );                     // 2
    lua_pushnumber( lua, static_cast<int>(sf::Keyboard::K) ); // 3
    lua_settable( lua, -3 );                        // 1
    lua_pushstring( lua, "U" );                     // 2
    lua_pushnumber( lua, static_cast<int>(sf::Keyboard::U) ); // 3
    lua_settable( lua, -3 );                        // 1
    lua_pushstring( lua, "I" );                     // 2
    lua_pushnumber( lua, static_cast<int>(sf::Keyboard::I) ); // 3
    lua_settable( lua, -3 );                        // 1
    lua_setglobal( lua, "input" );                  // 0
}

//------------------------------------------------------------------------------
