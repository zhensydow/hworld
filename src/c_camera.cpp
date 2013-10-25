/** @file c_camera.cpp
    @brief Camera Component Definition.
    @author Luis Cabellos
    @date 2013-10-20
*/
//------------------------------------------------------------------------------
#include "c_camera.hpp"
#include <iostream>

//------------------------------------------------------------------------------
int ccamera_getFov( lua_State * lua ){
    int n = lua_gettop( lua );    
    if( n != 1 ){
        lua_pushstring( lua, "incorrect number of arguments");
        lua_error( lua );
        return 0;
    }

    lua_pushstring( lua, "_comp" );
    lua_rawget( lua, -2 );
    auto component = static_cast<CCamera*>( lua_touserdata( lua, -1 ) );
    if( component ){
        auto fov = component->getFov();
        lua_pushnumber( lua, fov );
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
int ccamera_setFov( lua_State * lua ){
    int n = lua_gettop( lua );    
    if( n != 2 ){
        lua_pushstring( lua, "incorrect number of arguments");
        lua_error( lua );
        return 0;
    }

    auto fov = luaL_checknumber( lua, -1 );

    lua_pushstring( lua, "_comp" );
    lua_rawget( lua, -3 );
    auto component = static_cast<CCamera*>( lua_touserdata( lua, -1 ) );
    if( component ){
        component->setFov( fov );
    }

    return 0;
}

//------------------------------------------------------------------------------
Component::ScriptTable CCamera::s_cameraTable = {
    { "getFov", ccamera_getFov },
    { "setFov", ccamera_setFov },
};

//------------------------------------------------------------------------------
CCamera::CCamera( Entity & e ) : Component( e ) {
    registerScriptTable( &s_cameraTable );
}

//------------------------------------------------------------------------------
void CCamera::rotate_y( float angle ){
}

//------------------------------------------------------------------------------
