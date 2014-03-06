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
/** @file util.cpp
    @brief Util functions.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "util.hpp"
#include <random>
#include "lua.hpp"
#include "debug.hpp"

//------------------------------------------------------------------------------
Chunk createRandomChunk( int min, int max ){
    Chunk chunk;

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> dis( min, max );

    for( int i = 0 ; i < 7 ; ++i ){
        chunk.setHeight( i, dis( gen ) );
    }

    return chunk;
}

//------------------------------------------------------------------------------
ChunkProp createChunkProp( const Chunk & chunk ){
    ChunkProp cprop( chunk );

    return cprop;
}

//--------------------------------------------------------------------------
bool checkLuaReturn( lua_State * const ls, const int ret ){
    if( ret != 0 ){
        auto msg = lua_tostring( ls, -1);
        if( msg == nullptr ){
            logE( "Lua error object is not a string" );
        }else{
            logE( "Lua: ", msg );
        }
        // remove error message from stack
        lua_pop( ls, 1 );
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
bool lua_isUserData( lua_State * const ls, int idx, const std::string & str ){
    lua_getmetatable( ls, idx );              // +1
    luaL_getmetatable( ls, str.c_str() );     // +2
    auto ret = lua_equal( ls, -1, -2 ) == 1;  // +2
    lua_pop( ls, 2 );                         //  0
    return ret;
}

//------------------------------------------------------------------------------
