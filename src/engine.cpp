/** @file engine.cpp
    @brief Engine definitions.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#include "engine.hpp"
#include <iostream>
#include <SFML/System/Sleep.hpp>

//------------------------------------------------------------------------------
Engine::Engine(){
    //empty
}

//------------------------------------------------------------------------------
void Engine::setState( std::shared_ptr<GameState> state ){
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
        std::cout << " new state " << m_t << std::endl;
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


//------------------------------------------------------------------------------
