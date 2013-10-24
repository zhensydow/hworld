/** @file c_script.cpp
    @brief SCript Component Definition.
    @author Luis Cabellos
    @date 2013-10-22
*/
//------------------------------------------------------------------------------
#include "c_script.hpp"
#include <iostream>
#include <boost/filesystem.hpp>
#include "util.hpp"

//------------------------------------------------------------------------------
using namespace boost::filesystem;

//------------------------------------------------------------------------------
constexpr ComponentType CScript::type;

//------------------------------------------------------------------------------
CScript::CScript( Entity & e ) : Component( e ) {
    //empty
}

//------------------------------------------------------------------------------
void CScript::load( const std::string & filename ){
    if( !is_regular_file(filename) ){
        std::cout << "Not file '" << filename << "'" << std::endl;
    }

    // Lua Initialization
    m_lua = luaL_newstate();
    if( !m_lua ){
        std::cout << "Can't create Lua State" << std::endl;
    }

    lua_gc( m_lua, LUA_GCSTOP, 0 );
    luaL_openlibs( m_lua );
    lua_gc( m_lua, LUA_GCRESTART, 0 );

    // execute class file
    auto ret = luaL_dofile( m_lua, filename.c_str() );
    if( !checkLuaReturn( m_lua, ret ) ){
        m_lua = nullptr;
    }
}

//------------------------------------------------------------------------------
