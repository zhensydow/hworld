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
/** @file chunk.cpp
    @brief Chunk class definition.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "chunk.hpp"

//------------------------------------------------------------------------------
Chunk::Chunk(){
    std::fill( m_neighbours.begin(), m_neighbours.end(), CHUNK_NULL_IDX );
}

//------------------------------------------------------------------------------
bool Chunk::insertEntity( uint8_t tile, EntityID id ){
    if( tile >= NTILES ){
        return false;
    }

    m_entities.emplace_back( std::make_pair(tile,id) );

    return true;
}

//------------------------------------------------------------------------------
bool Chunk::hasEntity( uint8_t tile ) const{
    if( tile >= NTILES ){
        return false;
    }

    for( const auto & p: m_entities ){
        if( std::get<0>( p ) == tile ){
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
