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
/** @file script_glm.cpp
    @brief GLM script library.
    @author Luis Cabellos
    @date 2014-01-23
*/
//------------------------------------------------------------------------------
#include "script.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
void lua_push_vec4( lua_State * lua, const glm::vec4 & vec ){
    auto lua_val = (glm::vec4 *)lua_newuserdata( lua, sizeof(glm::vec4) ); // +1
    *lua_val = vec;
    luaL_getmetatable( lua, "glm_vec4" );  // +2
    lua_setmetatable( lua, -2 );           // +1
}

//------------------------------------------------------------------------------
void lua_push_mat4x4( lua_State * lua, const glm::mat4x4 & mat ){
    auto lua_val = (glm::mat4x4 *)lua_newuserdata( lua, sizeof(glm::mat4x4)); // +1
    *lua_val = mat;
    luaL_getmetatable( lua, "glm_mat4x4" ); // +2
    lua_setmetatable( lua, -2 );            // +1
}

//------------------------------------------------------------------------------
int glm_rotate( lua_State * lua ){
    int n = lua_gettop( lua );
    if( n != 4 ){
        return luaL_error( lua, "Got %d arguments expected 4", n );
    }

    auto angle = float( luaL_checknumber( lua, 1 ) );
    auto xa = float( luaL_checknumber( lua, 2 ) );
    auto ya = float( luaL_checknumber( lua, 3 ) );
    auto za = float( luaL_checknumber( lua, 4 ) );
    auto rot = glm::rotate( angle, xa, ya, za );

    lua_push_mat4x4( lua, rot );

    return 1;
}

//------------------------------------------------------------------------------
int glm_vec4( lua_State * lua ){
    int n = lua_gettop( lua );
    if( n != 4 ){
        return luaL_error( lua, "Got %d arguments expected 4", n );
    }

    auto x = luaL_checknumber( lua, 1 );
    auto y = luaL_checknumber( lua, 2 );
    auto z = luaL_checknumber( lua, 3 );
    auto w = luaL_checknumber( lua, 4 );

    lua_push_vec4( lua, glm::vec4( x, y, z, w ) );

    return 1;
}

//------------------------------------------------------------------------------
int glm_vec4_get( lua_State * lua ){
    int n = lua_gettop( lua );
    if( n != 2 ){
        return luaL_error( lua, "Got %d arguments expected 2", n );
    }

    glm::vec4 * vec = (glm::vec4 *) luaL_checkudata( lua, 1, "glm_vec4" );
    auto i = luaL_checknumber( lua, 2 );

    if( vec ){
        lua_pushnumber( lua, (*vec)[i] );
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
int glm_mat4x4_get( lua_State * lua ){
    int n = lua_gettop( lua );
    if( n != 3 ){
        return luaL_error( lua, "Got %d arguments expected 3", n );
    }

    glm::mat4x4 * mat = (glm::mat4x4 *) luaL_checkudata( lua, 1, "glm_mat4x4" );
    auto i = luaL_checknumber( lua, 2 );
    auto j = luaL_checknumber( lua, 3 );

    if( mat ){
        lua_pushnumber( lua, (*mat)[i][j] );
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
int glm_mat4x4_mul( lua_State * lua ){
    int n = lua_gettop( lua );
    if( n != 2 ){
        return luaL_error( lua, "Got %d arguments expected 2", n );
    }

    glm::mat4x4 * mat = (glm::mat4x4 *) luaL_checkudata( lua, 1, "glm_mat4x4" );

    if( lua_isUserData( lua, 2, "glm_vec4" ) ){
        auto vec = (glm::vec4 *) luaL_checkudata( lua, 2, "glm_vec4" );
        lua_push_vec4( lua, (*mat) * (*vec) );
        return 1;
    }else if( lua_isUserData( lua, 2, "glm_mat4x4" ) ){
        auto mat2 = (glm::mat4x4 *) luaL_checkudata( lua, 1, "glm_mat4x4" );
        lua_push_mat4x4( lua, (*mat) * (*mat2) );
        return 1;
    }else{
        return luaL_error( lua, "Invalid value to multiply with mat4x4" );
    }
}

//------------------------------------------------------------------------------
const luaL_Reg glmLib[] = {
    {"rotate", glm_rotate},
    {"vec4", glm_vec4},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
const luaL_Reg glm_mat4x4Lib[] = {
    {"get", glm_mat4x4_get},
    {"mul", glm_mat4x4_mul},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
const luaL_Reg glm_vec4Lib[] = {
    {"get", glm_vec4_get},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openGLM( lua_State * lua ){
    luaL_register( lua, "glm", glmLib );

    luaL_newmetatable( lua, "glm_mat4x4");
    luaL_register( lua, nullptr, glm_mat4x4Lib );
    lua_pushvalue( lua, -1 );
    lua_setfield( lua, -2, "__index" );

    luaL_newmetatable( lua, "glm_vec4");
    luaL_register( lua, nullptr, glm_vec4Lib );
    lua_pushvalue( lua, -1 );
    lua_setfield( lua, -2, "__index" );
}

//------------------------------------------------------------------------------
