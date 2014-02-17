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
/** @file chunk.hpp
    @brief Chunk Class Definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef CHUNK_HPP_
#define CHUNK_HPP_

//------------------------------------------------------------------------------
#include <array>
#include <limits>
#include <vector>
#include <tuple>

//------------------------------------------------------------------------------
constexpr unsigned int CHUNK_NULL_IDX = std::numeric_limits<unsigned int>::max();

//------------------------------------------------------------------------------
class Chunk{
public:
    constexpr static unsigned int NTILES = 7;
    constexpr static unsigned int NNEIGHBOURS = 6;
    constexpr static unsigned int VERTS_TILE = 6;
    constexpr static float STEP_SIZE = 0.2f;

    Chunk();

    void setHeight( unsigned int i, const int val );

    bool hasEntity( unsigned int tile ) const;

    std::array< int, NTILES > m_heights;
    std::array< unsigned int, NNEIGHBOURS > m_neighbours;
    std::vector< std::tuple<unsigned int, unsigned int> > m_entities;
};

//------------------------------------------------------------------------------
inline
void Chunk::setHeight( unsigned int i, const int val ){
    if( i < NTILES ){
        m_heights[ i ] = val;
    }
}

//------------------------------------------------------------------------------
#endif//CHUNK_HPP_

//------------------------------------------------------------------------------
