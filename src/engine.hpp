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

//------------------------------------------------------------------------------
class GameState;

//------------------------------------------------------------------------------
class Engine {
public:
    Engine();

    void update();

    bool isRunning() const;

    void stop();

    void yield();

    void setState( std::shared_ptr<GameState> state );

    std::shared_ptr<GameState> makeGameState( const std::string & name ) const;

private:
    enum class NextState{
        NEW_STATE,
            PUSH_STATE,
            POP_STATE,
            NOTHING
    };

    static constexpr double FRAMES_PER_SECOND = 10.0;
    static constexpr double dt = 1.0 / FRAMES_PER_SECOND;
    static constexpr double MAX_FRAME_TIME = 0.25;

    sf::Clock m_clock;
    std::stack< std::shared_ptr<GameState> > m_states;

    NextState m_nextStateType = NextState::NOTHING;
    std::shared_ptr<GameState> m_nextState = nullptr;

    boost::filesystem::path m_datadir = "data";

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
#endif//ENGINE_HPP_

//------------------------------------------------------------------------------
