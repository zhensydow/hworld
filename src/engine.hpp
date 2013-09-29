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
#include <SFML/System/Sleep.hpp>
#include "gamestate.hpp"

//------------------------------------------------------------------------------
class Engine {
public:
    Engine();

    void update();

    bool isRunning() const;

    void stop();

    void yield() const;

    void setState( std::shared_ptr<GameState> state );

private:
    static constexpr double FRAMES_PER_SECOND = 10.0;
    static constexpr double dt = 1.0 / FRAMES_PER_SECOND;
    static constexpr double MAX_FRAME_TIME = 0.25;

    sf::Clock m_clock;
    std::stack< std::shared_ptr<GameState> > m_states;

    double m_t = 0.0;
    double m_accum = 0.0;

    bool m_running = true;
};

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
void Engine::yield() const{
    sf::sleep( sf::milliseconds(1) );
}

//------------------------------------------------------------------------------
#endif//ENGINE_HPP_

//------------------------------------------------------------------------------
