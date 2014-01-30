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
GameState::GameState() noexcept : m_ls{nullptr} {
    //empty
    std::cout << "GameState empty constructor" << std::endl;
}

//------------------------------------------------------------------------------
GameState::GameState( lua_State * ls ) noexcept : m_ls{ls} {
    //empty
    std::cout << "GameState constructor" << std::endl;
}

GameState::GameState( GameState&& gs ) noexcept {
    m_ls = std::move( gs.m_ls );
    gs.m_ls = nullptr;
}

GameState& GameState::operator=( GameState&& gs ) noexcept {
    m_ls = std::move( gs.m_ls );
    gs.m_ls = nullptr;
    return *this;
}

//------------------------------------------------------------------------------
GameState::~GameState() noexcept{
    std::cout << "GameState destructor" << std::endl;
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
