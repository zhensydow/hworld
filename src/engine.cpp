/** @file engine.cpp
    @brief Engine definitions.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#include "engine.hpp"
#include <iostream>
#include <SFML/System/Sleep.hpp>
#include "lua.hpp"
#include "gs_lua.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
using namespace std;
using namespace boost::filesystem;

//------------------------------------------------------------------------------
Engine::Engine(){
    //empty
}

//------------------------------------------------------------------------------
void Engine::setState( shared_ptr<GameState> state ){
    if( state ){
        m_nextState = state;
        m_nextStateType = NextState::NEW_STATE;
    }
}

//------------------------------------------------------------------------------
void Engine::update(){
    double frameTime = m_clock.restart().asSeconds();
    if( frameTime > MAX_FRAME_TIME ){
        frameTime = MAX_FRAME_TIME;
    }

    m_accum += frameTime;
    while( m_accum >= dt ){
        if( not m_states.empty() ){
            auto state = m_states.top();
            state->update( dt );
        }
        m_t += dt;
        m_accum -= dt;
    }

}

//------------------------------------------------------------------------------
void Engine::yield(){
    switch( m_nextStateType ){
    case NextState::NEW_STATE:
        cout << " new state " << m_t << endl;
        if( not m_states.empty() ){
            auto old = m_states.top();
            if( old ){
                old->stop();
            }
            m_states.pop();
        }
        m_states.push( m_nextState );
        m_nextState->start();

        m_nextStateType = NextState::NOTHING;
        m_nextState = nullptr;
        break;

    default:
        break;
    }

    sf::sleep( sf::milliseconds(1) );
}

//--------------------------------------------------------------------------
/** List of functions of AgentClass lua library for Agent files.
*/
const luaL_Reg enginelib[] = {
    //{"newstate",  engine_newstate},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
shared_ptr<GameState> Engine::makeGSLua( const string & name ) const{
    auto statedir = path(m_datadir) /= "state";
    auto filename = statedir /= (name + ".lua");

    if( !is_regular_file( filename ) ){
        cout << "Not file for class '" <<  name << "'" << endl;
        return nullptr;
    }

    // Lua Initialization
    auto ls = luaL_newstate();
    if( !ls ){
        cout << "Can't create Lua State" << endl;
        return nullptr;
    }

    lua_gc( ls, LUA_GCSTOP, 0 );
    luaL_openlibs( ls );
    // set engine functions
    luaL_register( ls, "engine", enginelib );
    lua_pushlightuserdata( ls, (void*)this );
    lua_setfield( ls, -2, "_this" );
    // removes table
    lua_pop( ls, 1 );
    lua_gc( ls, LUA_GCRESTART, 0 );

    // create Lua Game State
    auto state = make_shared<GSLua>( ls );
    if( !state ){
        lua_close( ls );
        cout << "Can't create agent class '" << name << "' instance" << endl;
        return nullptr;
    }

    // execute class file
    auto ret = luaL_dofile( ls, filename.c_str() );
    if( !checkLuaReturn( ls, ret ) ){
        return nullptr;
    }

    return state;
}

//------------------------------------------------------------------------------
