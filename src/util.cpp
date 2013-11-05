/** @file util.cpp
    @brief Util functions.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "util.hpp"
#include <random>
#include "lua.hpp"

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
            std::cout << "Lua error object is not a string" << std::endl;
        }else{
            std::cout << "Lua: " << msg << std::endl;
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
