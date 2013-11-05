//------------------------------------------------------------------------------
#include "script.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

//------------------------------------------------------------------------------
int glm_rotate( lua_State * lua ){
    int n = lua_gettop( lua );
    if( n != 4 ){
        return luaL_error( lua, "Got %d arguments expected 4", n );
    }

    auto angle = luaL_checknumber( lua, 1 );
    auto xa = luaL_checknumber( lua, 2 );
    auto ya = luaL_checknumber( lua, 3 );
    auto za = luaL_checknumber( lua, 4 );
    auto rot = glm::rotate( angle, xa, ya, za );

    glm::mat4x4 *mat = (glm::mat4x4 *)lua_newuserdata( lua, sizeof(glm::mat4x4));

    *mat = rot;

    luaL_getmetatable( lua, "glm_mat4x4");
    lua_setmetatable( lua, -2);

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

    glm::vec4 * ret = (glm::vec4 *)lua_newuserdata( lua, sizeof(glm::vec4));

    *ret = glm::vec4( x, y, z, w );

    luaL_getmetatable( lua, "glm_vec4");
    lua_setmetatable( lua, -2);

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
    }

    return 0;
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
