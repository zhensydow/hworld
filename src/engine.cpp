/** @file engine.cpp
    @brief Engine definitions.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#include "engine.hpp"
#include <iostream>

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
            if( state ){
                state->update( dt );
            }else{
                m_states.pop();
            }
        }
        std::cout << " update " << m_t << std::endl;
        m_t += dt;
        m_accum -= dt;
    }

}

//------------------------------------------------------------------------------
