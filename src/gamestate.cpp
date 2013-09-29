/** @file gamestate.cpp
    @brief Game State definitions.
    @author Luis Cabellos
    @date 2013-09-29
*/
//------------------------------------------------------------------------------
#include "gamestate.hpp"
#include "lua.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
GameState::GameState( lua_State * ls ) : m_ls{ls} {
    //empty
}

//------------------------------------------------------------------------------
GameState::~GameState(){
    if( m_ls ){
        lua_close( m_ls );
    }
}

//------------------------------------------------------------------------------
void GameState::start(){
    if( m_ls ){
        lua_getfield( m_ls, LUA_GLOBALSINDEX, "start" );     // 1
        if( lua_isfunction( m_ls, -1 ) ){
            auto ret = lua_pcall( m_ls, 0, 0, 0 );           // 0
            checkLuaReturn( m_ls, ret );
        }
    }
}

//------------------------------------------------------------------------------
void GameState::update( double dt ){
    if( m_ls ){
        lua_getfield( m_ls, LUA_GLOBALSINDEX, "update" );    // 1
        if( lua_isfunction( m_ls, -1 ) ){
            lua_pushnumber( m_ls, dt );                      // 2
            auto ret = lua_pcall( m_ls, 1, 0, 0 );           // 0
            checkLuaReturn( m_ls, ret );
        }
    }
}

//------------------------------------------------------------------------------
void GameState::stop(){
    if( m_ls ){
        lua_getfield( m_ls, LUA_GLOBALSINDEX, "stop" );      // 1
        if( lua_isfunction( m_ls, -1 ) ){
            auto ret = lua_pcall( m_ls, 0, 0, 0 );           // 0
            checkLuaReturn( m_ls, ret );
        }
    }
}

//------------------------------------------------------------------------------
