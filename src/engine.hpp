/** @file engine.hpp
    @brief Engine declaration.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#ifndef ENGINE_HPP_
#define ENGINE_HPP_

//------------------------------------------------------------------------------
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

//------------------------------------------------------------------------------
class Engine {
public:
    void update();

    bool isRunning() const;

    void stop();

    void yield() const;

private:
    static constexpr double FRAMES_PER_SECOND = 10.0;
    static constexpr double dt = 1.0 / FRAMES_PER_SECOND;
    static constexpr double MAX_FRAME_TIME = 0.25;

    sf::Clock m_clock;
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
