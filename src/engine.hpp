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
/** @file engine.hpp
    @brief Engine declaration.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#ifndef ENGINE_HPP_
#define ENGINE_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include <stack>
#include <SFML/System/Clock.hpp>
#include <boost/filesystem.hpp>
#include "gamestate.hpp"
#include "world.hpp"
#include "terminal.hpp"
#include "gfx.hpp"
#include "input.hpp"
#include "resourcefactory.hpp"

//------------------------------------------------------------------------------
class Entity;
class IUpdate;
class IDrawable;
class Config;
class TerrainProp;

//------------------------------------------------------------------------------
class Engine {
public:
    static Engine & instance();

    std::string getDataFilename( const boost::filesystem::path & filename ) const;

    void setup( const Config & config );
    void destroy();

    bool isRunning() const;
    void update();
    void draw();
    void yield();
    void stop();

    unsigned int terrainFocus() const;
    void setTerrainFocus( unsigned int idx );

    World & getWorld();
    Gfx & getGfx();
    Input & getInput();
    Terminal & getTerminal();
    ResourceFactory & getResourceFactory();

    void setState( std::unique_ptr<GameState> state );

    std::unique_ptr<GameState> makeGameState( const std::string & name ) const;

    std::shared_ptr<Entity> getEntity( const unsigned int id ) noexcept;
    void addEntity( std::shared_ptr<Entity> entity );
    bool hasCamera() noexcept;
    void setCamera( std::shared_ptr<Entity> entity ) noexcept;

    double getTime() const noexcept;

private:
    Engine();

    void updateCamera();

    enum class NextState{
        NEW_STATE,
            PUSH_STATE,
            POP_STATE,
            NOTHING
    };

    static constexpr double FRAMES_PER_SECOND = 60.0;
    static constexpr double dt = 1.0 / FRAMES_PER_SECOND;
    static constexpr double MAX_FRAME_TIME = 0.25;

    sf::Clock m_clock;
    std::stack< GameState > m_states;

    NextState m_nextStateType = NextState::NOTHING;
    std::unique_ptr<GameState> m_nextState = nullptr;

    Gfx m_gfx;
    Input m_input;
    World m_world;
    Terminal m_terminal;
    ResourceFactory m_resourceFactory;

    std::unique_ptr<TerrainProp> m_terrain;

    boost::filesystem::path m_datadir = "";

    std::vector< std::shared_ptr<Entity> > m_entities;
    std::vector< std::shared_ptr<IUpdate> > m_updateList;
    std::vector< std::shared_ptr<IDrawable> > m_drawableList;

    std::shared_ptr<Entity> m_camera = nullptr;

    double m_t = 0.0;
    double m_accum = 0.0;

    bool m_running = true;
};

//------------------------------------------------------------------------------
inline
std::string Engine::getDataFilename( const boost::filesystem::path & filename ) const
{
    auto final = boost::filesystem::path(m_datadir) /= filename;
    return final.native();
}

//------------------------------------------------------------------------------
inline
bool Engine::isRunning() const{
    return m_running;
}

//------------------------------------------------------------------------------
inline
void Engine::stop() {
    m_running = false;
}

//------------------------------------------------------------------------------
inline
World & Engine::getWorld(){
    return m_world;
}

//------------------------------------------------------------------------------
inline
Gfx & Engine::getGfx(){
    return m_gfx;
}

//------------------------------------------------------------------------------
inline
Input & Engine::getInput(){
    return m_input;
}

//------------------------------------------------------------------------------
inline
Terminal & Engine::getTerminal(){
    return m_terminal;
}

//------------------------------------------------------------------------------
inline
ResourceFactory & Engine::getResourceFactory(){
    return m_resourceFactory;
}

//------------------------------------------------------------------------------
inline
void Engine::setCamera( std::shared_ptr<Entity> cam ) noexcept {
    m_camera = cam;
}

//------------------------------------------------------------------------------
inline
bool Engine::hasCamera() noexcept {
    return m_camera != nullptr;
}

//------------------------------------------------------------------------------
inline
double Engine::getTime() const noexcept{
    return m_accum;
}

//------------------------------------------------------------------------------
#endif//ENGINE_HPP_

//------------------------------------------------------------------------------
