/** @file util.hpp
    @brief Util functions.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef UTIL_HPP_
#define UTIL_HPP_

//------------------------------------------------------------------------------

#include "chunk.hpp"
#include "chunkprop.hpp"

//------------------------------------------------------------------------------
struct lua_State;

//------------------------------------------------------------------------------
Chunk createRandomChunk( int min, int max );
ChunkProp createChunkProp( const Chunk & chunk );
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
