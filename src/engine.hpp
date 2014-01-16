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
#include "terrainprop.hpp"
#include "terminal.hpp"
#include "renderer.hpp"
#include "resourcefactory.hpp"

//------------------------------------------------------------------------------
class Entity;
class IUpdate;
class IDrawable;
class Config;

//------------------------------------------------------------------------------
class Engine {
public:
    static Engine & instance();

    std::string getDataFilename( const std::string & filename ) const;

    void setup( const Config & config );
    void destroy();

    bool isRunning() const;
    void update();
    void draw();
    void yield();
    void stop();

    World & getWorld();
    Renderer & getRenderer();
    Terminal & getTerminal();
    ResourceFactory & getResourceFactory();

    void setState( std::unique_ptr<GameState> state );

    std::unique_ptr<GameState> makeGameState( const std::string & name ) const;

    void addEntity( std::shared_ptr<Entity> entity );
    void setCamera( std::shared_ptr<Entity> entity ) noexcept;

private:
    Engine();

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

    Renderer m_renderer;
    World m_world;
    Terminal m_terminal;
    ResourceFactory m_resourceFactory;

    std::unique_ptr<TerrainProp> m_terrain;

    boost::filesystem::path m_datadir = "data";

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
std::string Engine::getDataFilename( const std::string & filename ) const{
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
Renderer & Engine::getRenderer(){
    return m_renderer;
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
#endif//ENGINE_HPP_

//------------------------------------------------------------------------------
