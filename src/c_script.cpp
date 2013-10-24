/** @file c_script.cpp
    @brief SCript Component Definition.
    @author Luis Cabellos
    @date 2013-10-22
*/
//------------------------------------------------------------------------------
#include "c_script.hpp"
#include <iostream>
#include <boost/filesystem.hpp>
#include <luabind/luabind.hpp>
#include <SFML/Graphics.hpp>
#include "util.hpp"

//------------------------------------------------------------------------------
using namespace boost::filesystem;

//------------------------------------------------------------------------------
constexpr ComponentType CScript::type;

//------------------------------------------------------------------------------
CScript::CScript( Entity & e ) : Component( e ) {
    //empty
}

//------------------------------------------------------------------------------
CScript::~CScript(){
    if( m_lua ){
        lua_close( m_lua );
    }
}

bool isKeyPressed( int val ){
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(val));
}

//------------------------------------------------------------------------------
int entity_index( lua_State *lua ){
    std::string name = luaL_checkstring( lua, 2 );
    std::cout << "GET INDEX " << name << std::endl;
    return 0;
}

//------------------------------------------------------------------------------
int entity_newindex( lua_State *lua ){
    std::string name = luaL_checkstring( lua, 2 );
    std::cout << "NEW INDEX " << name << std::endl;
    return 0;
}

//------------------------------------------------------------------------------
void CScript::load( const std::string & filename ){
    if( !is_regular_file(filename) ){
        std::cout << "Not file '" << filename << "'" << std::endl;
    }

    // Lua Initialization
    m_lua = luaL_newstate();
    if( !m_lua ){
        std::cout << "Can't create Lua State" << std::endl;
    }

    lua_gc( m_lua, LUA_GCSTOP, 0 );
    luaL_openlibs( m_lua );

    // set input
    luabind::module( m_lua, "input" )
        [
         luabind::def("isKeyPressed", &(isKeyPressed) )
         ];

    lua_getglobal( m_lua, "input" );                  // 1
    lua_pushstring( m_lua, "U" );                     // 2
    lua_pushnumber( m_lua, static_cast<int>(sf::Keyboard::U) ); // 3
    lua_settable( m_lua, -3 );                        // 1
    lua_pushstring( m_lua, "I" );                     // 2
    lua_pushnumber( m_lua, static_cast<int>(sf::Keyboard::I) ); // 3
    lua_settable( m_lua, -3 );                        // 1
    lua_pop( m_lua, 1 );                              // 0

    // set entity
    lua_newtable( m_lua );                             // 1
    luaL_newmetatable( m_lua, "entity" );              // 2
    lua_pushstring( m_lua, "__newindex");              // 3
    lua_pushcfunction( m_lua, entity_newindex );       // 4
    lua_settable( m_lua, -3 );                         // 2
    lua_pushstring( m_lua, "__index");                 // 3
    lua_pushcfunction( m_lua, entity_index );          // 4
    lua_settable( m_lua, -3 );                         // 2
    lua_setmetatable( m_lua, -2 );                     // 1
    lua_setfield( m_lua, LUA_GLOBALSINDEX, "entity" ); // 0

    lua_gc( m_lua, LUA_GCRESTART, 0 );

    // execute class file
    auto ret = luaL_dofile( m_lua, filename.c_str() );
    if( !checkLuaReturn( m_lua, ret ) ){
        m_lua = nullptr;
    }
}

//------------------------------------------------------------------------------
void CScript::update( double d ){
    if( m_lua ){
        lua_getfield( m_lua, LUA_GLOBALSINDEX, "onUpdate" );     // 1
        if( lua_isfunction( m_lua, -1 ) ){
            lua_pushnumber( m_lua, d );                          // 2
            auto ret = lua_pcall( m_lua, 1, 0, 0 );              // 0
            checkLuaReturn( m_lua, ret );
        }else{
            lua_pop( m_lua, 1 );                                 // 0
        }
    }
}

//------------------------------------------------------------------------------
