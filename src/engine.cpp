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
#include "util.hpp"
#include "gamestate.hpp"
#include "entity.hpp"
#include "c_transform.hpp"
#include "c_camera.hpp"
#include "c_script.hpp"
#include "script.hpp"

//------------------------------------------------------------------------------
using namespace std;
using namespace boost::filesystem;

sf::Sprite spr;
sf::Texture tex;

//------------------------------------------------------------------------------
Engine & Engine::instance(){
    static Engine s_engine;
    return s_engine;
}

//------------------------------------------------------------------------------
Engine::Engine() : m_nextState{nullptr} {
    //empty
}

//------------------------------------------------------------------------------
void Engine::setup(){
    m_renderer.setup();

    m_terminal.initialize();

    m_terrain = unique_ptr<TerrainProp>( new TerrainProp(m_world) );
    m_terrain->setFocus( 0 );

    if( !tex.loadFromFile( getDataFilename( "template.png" ) ) ){
        std::terminate();
    }

    spr.setTexture( tex, true );
}

//------------------------------------------------------------------------------
void Engine::setState( std::unique_ptr<GameState> state ){
    if( state ){
        m_nextState = std::move(state);
        m_nextStateType = NextState::NEW_STATE;
    }
}

//------------------------------------------------------------------------------
void Engine::addEntity( shared_ptr<Entity> entity ){
    if( entity ){
        m_entities.push_back( entity );

        auto comp = entity->getComponent<CScript>();
        if( comp ){
            m_updateList.push_back( std::static_pointer_cast<IUpdate>(comp) );
        }
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
        for( auto & comp: m_updateList ){
            comp->update( dt );
        }

        if( not m_states.empty() ){
            auto & state = m_states.top();
            state.update( dt );
        }
        m_t += dt;
        m_accum -= dt;
    }

}

//------------------------------------------------------------------------------
void Engine::draw(){
    if( m_camera ){
        auto ctrans = m_camera->getComponent<CTransform>();
        auto ccam = m_camera->getComponent<CCamera>();
        if( ctrans and ccam ){
            auto eye = ctrans->getGlobalPosition();
            m_renderer.view = glm::lookAt( eye, glm::vec3(0,0,0), glm::vec3(0,1,0) );
            m_renderer.proj = ccam->getProjection();
        }
    }

    m_renderer.startFrame();

    m_terrain->draw( m_renderer );

    m_renderer.startGUI();

    m_terminal.draw( m_renderer );

    auto window = m_renderer.getWindow();
    window->draw( spr );

    m_renderer.endFrame();
}

//------------------------------------------------------------------------------
void Engine::yield(){
    switch( m_nextStateType ){
    case NextState::NEW_STATE:
        cout << " new state " << m_t << endl;
        if( not m_states.empty() ){
            auto old = std::move(m_states.top());
            m_states.pop();
            old.stop();
        }
        if( m_nextState ){
            m_nextState->start();
            m_states.push( std::move(*m_nextState) );
        }

        m_nextStateType = NextState::NOTHING;
        m_nextState = nullptr;
        break;

    default:
        break;
    }

    sf::sleep( sf::milliseconds(1) );
}

//--------------------------------------------------------------------------
int engine_newstate( lua_State *ls ){
    auto str = luaL_checkstring( ls, 1 );
    lua_getfield( ls, LUA_GLOBALSINDEX, "engine" );
    lua_getfield( ls, -1, "_this");
    lua_remove( ls, -2 );
    if( lua_islightuserdata( ls, -1 ) ){
        auto engine = (Engine*) lua_topointer( ls, -1 );
        auto state = engine->makeGameState( str );
        engine->setState( std::move(state) );
    }

    return 0;
}

//--------------------------------------------------------------------------
/** List of functions of AgentClass lua library for Agent files.
*/
const luaL_Reg enginelib[] = {
    {"newstate",  engine_newstate},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
unique_ptr<GameState> Engine::makeGameState( const string & name ) const{
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
    openInput( ls );
    openTerminal( ls );
    // set engine functions
    luaL_register( ls, "engine", enginelib );
    lua_pushlightuserdata( ls, (void*)this );
    lua_setfield( ls, -2, "_this" );
    // removes table
    lua_pop( ls, 1 );
    lua_gc( ls, LUA_GCRESTART, 0 );

    // create Lua Game State
    auto state = std::unique_ptr<GameState>(new GameState( ls ) );
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
