/**
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
**/
/** @file engine.cpp
    @brief Engine definitions.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#include "engine.hpp"
#include "util.hpp"
#include "entity.hpp"
#include "c_transform.hpp"
#include "c_camera.hpp"
#include "c_staticmodel.hpp"
#include "c_script.hpp"
#include "script.hpp"
#include "terrainprop.hpp"
#include "config.hpp"

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
void Engine::setup( const Config & config ){
    m_datadir = config.datadir;

    m_gfx.setup( config );

    m_terminal.initialize();

    m_terrain = unique_ptr<TerrainProp>( new TerrainProp(m_world) );
    m_terrain->setFocus( 0 );

    if( !tex.loadFromFile( getDataFilename( "gfx/template.png" ) ) ){
        std::terminate();
    }

    spr.setTexture( tex, true );

    if( config.initialState != "" ){
        setState( makeGameState( config.initialState ) );
    }
}

//------------------------------------------------------------------------------
void Engine::destroy(){
    m_gfx.destroy();
}

//------------------------------------------------------------------------------
void Engine::setState( unique_ptr<GameState> state ){
    if( state ){
        m_nextState = move(state);
        m_nextStateType = NextState::NEW_STATE;
    }
}

//------------------------------------------------------------------------------
shared_ptr<Entity> Engine::getEntity( const unsigned int id ) noexcept{
    auto it = find_if( begin(m_entities), end(m_entities),
                       [id]( shared_ptr<Entity> & e){ return e->id() == id; } );

    if( it != end(m_entities) ){
        return *it;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
void Engine::addEntity( shared_ptr<Entity> entity ){
    if( entity ){
        m_entities.push_back( entity );

        auto scomp = entity->getComponent<CScript>();
        if( scomp ){
            m_updateList.push_back( static_pointer_cast<IUpdate>(scomp) );
        }

        auto mcomp = entity->getComponent<CStaticModel>();
        if( mcomp ){
            m_drawableList.push_back( static_pointer_cast<IDrawable>(mcomp) );
        }
    }
}

//------------------------------------------------------------------------------
void Engine::update(){
    double frameTime = m_clock.restart().asSeconds();
    if( frameTime > MAX_FRAME_TIME ){
        frameTime = MAX_FRAME_TIME;
    }

    m_input.beginFrame();

    auto window = m_gfx.getWindow();
    sf::Event event;
    while( window->pollEvent(event) ){
        if( event.type == sf::Event::Closed ){
            stop();
        }else if( event.type == sf::Event::Resized ){
            m_gfx.setViewport( event.size.width, event.size.height );
            m_terminal.resize( event.size.width, event.size.height );
        }else if( event.type == sf::Event::KeyReleased ){
            if( event.key.code == sf::Keyboard::Tab ){
                m_terminal.setVisible( not m_terminal.isVisible() );
            }
            m_input.setKeyReleased( event.key.code );
        }else if( event.type == sf::Event::KeyPressed ){
            m_input.setKeyPressed( event.key.code );
        }
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
void Engine::updateCamera() {
    if( m_camera ){
        auto ctrans = m_camera->getComponent<CTransform>();
        auto ccam = m_camera->getComponent<CCamera>();
        if( ctrans and ccam ){
            auto eye = ctrans->getGlobalPosition();
            auto obj = glm::vec3(0,0,0);
            auto tmp = eye - obj;
            auto dist = glm::dot( tmp, tmp );
            // if eye and obj are the same point, we get division by zero
            if( dist > 0.001 ){
                m_gfx.view = glm::lookAt( eye, obj,
                                           glm::vec3(0,1,0) );
                auto fov = ccam->getFov();
                m_gfx.proj = glm::perspective( fov,
                                               m_gfx.aspectRatio(),
                                               0.1f, 100.0f );
            }
        }
    }
}

//------------------------------------------------------------------------------
void Engine::draw(){
    updateCamera();

    m_gfx.startFrame();

    m_gfx.startShadowMappingPass();

    auto renderer = m_gfx.getCurrentRenderer();
    if( renderer ){
        m_terrain->draw( *renderer );

        for( auto & comp: m_drawableList ){
            comp->draw( *renderer );
        }
    }

    m_gfx.startColorPass();

    renderer = m_gfx.getCurrentRenderer();
    if( renderer ){
        m_terrain->draw( *renderer );

        for( auto & comp: m_drawableList ){
            comp->draw( *renderer );
        }
    }

    m_gfx.startGUI();

    renderer = m_gfx.getCurrentRenderer();
    if( renderer ){
        m_terminal.draw( *renderer );
    }

    auto window = m_gfx.getWindow();
    window->draw( spr );

    m_gfx.endFrame();
}

//------------------------------------------------------------------------------
void Engine::yield(){
    switch( m_nextStateType ){
    case NextState::NEW_STATE:
        logI( "New state ", m_t );
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

//------------------------------------------------------------------------------
unique_ptr<GameState> Engine::makeGameState( const string & name ) const{
    auto statedir = path(m_datadir) /= "state";
    auto filename = statedir /= (name + ".lua");

    if( !is_regular_file( filename ) ){
        logE( "Not file for class '", name, "'" );
        return nullptr;
    }

    // Lua Initialization
    auto ls = luaL_newstate();
    if( !ls ){
        logE( "Can't create Lua State" );
        return nullptr;
    }

    lua_gc( ls, LUA_GCSTOP, 0 );
    luaL_openlibs( ls );
    openWorld( ls );
    openInput( ls );
    openTerminal( ls );
    openEngine( ls );
    openGame( ls );
    openGLM( ls );
    lua_gc( ls, LUA_GCRESTART, 0 );

    // create Lua Game State
    auto state = std::unique_ptr<GameState>(new GameState( ls ) );
    if( !state ){
        lua_close( ls );
        logE( "Can't create agent class '", name, "' instance" );
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
