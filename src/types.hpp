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
/** @file types.hpp
    @brief Basic Types definitions
    @author Luis Cabellos
    @date 2014-03-04
*/
//------------------------------------------------------------------------------
#ifndef TYPES_HPP_
#define TYPES_HPP_

//------------------------------------------------------------------------------
#include <limits>

//------------------------------------------------------------------------------
using ChunkID = unsigned int;

constexpr ChunkID CHUNK_NULL_IDX = std::numeric_limits<ChunkID>::max();

//------------------------------------------------------------------------------
using EntityID = unsigned int;

constexpr EntityID ENTITY_NULL_IDX = std::numeric_limits<EntityID>::max();

//------------------------------------------------------------------------------
#endif//TYPES_HPP_

//------------------------------------------------------------------------------
