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
/** @file world.cpp
    @brief World Definition.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#include "world.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
World::World(){
    // create a minimal world
    m_terrain[ 0 ] = createRandomChunk( -5, 5 );
}

//------------------------------------------------------------------------------
Chunk & World::getChunk( unsigned int idx ){
    return m_terrain[ idx ];
}

//------------------------------------------------------------------------------
