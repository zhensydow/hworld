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
/** @file input.hpp
    @brief Input class.
    @author Luis Cabellos
    @date 2014-01-20
*/
//------------------------------------------------------------------------------
#ifndef INPUT_HPP_
#define INPUT_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>

//------------------------------------------------------------------------------
class Input {
public:
    void beginFrame();

    void setKeyPressed( int key );
    void setKeyReleased( int key );

    bool isKeyDown( int key );
    bool isKeyUp( int key );

private:
    std::unordered_map< int, bool > m_down_map;
    std::unordered_map< int, bool > m_up_map;
};

//------------------------------------------------------------------------------
inline
void Input::beginFrame(){
    m_down_map.clear();
    m_up_map.clear();
}

//------------------------------------------------------------------------------
inline
void Input::setKeyPressed( int key ){
    m_down_map[key] = true;
}

//------------------------------------------------------------------------------
inline
void Input::setKeyReleased( int key ){
    m_up_map[key] = true;
}

//------------------------------------------------------------------------------
inline
bool Input::isKeyDown( int key ){
    return m_down_map[key];
}

//------------------------------------------------------------------------------
inline
bool Input::isKeyUp( int key ){
    return m_up_map[key];
}

//------------------------------------------------------------------------------
#endif//INPUT_HPP_

//------------------------------------------------------------------------------
