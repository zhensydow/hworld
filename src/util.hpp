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
/** @file util.hpp
    @brief Util functions.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef UTIL_HPP_
#define UTIL_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include "chunk.hpp"
#include "chunkprop.hpp"
#include "quadnode.hpp"

//------------------------------------------------------------------------------
struct lua_State;

//------------------------------------------------------------------------------
Chunk createRandomChunk( int min, int max );
ChunkProp createChunkProp( const Chunk & chunk );
std::unique_ptr<QuadNode> createWorldQuad( unsigned int levels, glm::vec2 minb, glm::vec2 maxb );

//------------------------------------------------------------------------------
/** Check a lua function return, and show error message if needed.
    @param ls Lua State.
    @param err Lua error state.
    @retval True if Lua Return Value is OK.
*/
bool checkLuaReturn( lua_State * const ls, const int err );
bool lua_isUserData( lua_State * const ls, int idx, const std::string & str );

//------------------------------------------------------------------------------
#endif//UTIL_HPP_

//------------------------------------------------------------------------------
