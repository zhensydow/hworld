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
/** @file gamestate.hpp
    @brief GameState declaration.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

//------------------------------------------------------------------------------
struct lua_State;

//------------------------------------------------------------------------------
class GameState final {
public:
    GameState() noexcept;
    GameState( lua_State * lua ) noexcept;
    GameState( const GameState& ) = delete;
    GameState( GameState&& ) noexcept;
    GameState& operator=( const GameState& ) = delete;
    GameState& operator=( GameState&& ) noexcept;
    ~GameState() noexcept;

    void start();
    void update( double dt );
    void stop();

    lua_State * getLua() const;

private:
    lua_State * m_ls = nullptr;
};

//------------------------------------------------------------------------------
inline
lua_State * GameState::getLua() const{
    return m_ls;
}

//------------------------------------------------------------------------------
#endif//GAMESTATE_HPP_

//------------------------------------------------------------------------------
