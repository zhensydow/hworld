/** @file worldarea.hpp
    @brief WorldArea definitions.
    @author Luis Cabellos
    @date 2014-05-05
*/
//------------------------------------------------------------------------------
#ifndef WORLDAREA_HPP_
#define WORLDAREA_HPP_

//------------------------------------------------------------------------------
#include "types.hpp"

//------------------------------------------------------------------------------
class WorldArea{
public:
    WorldArea( const glm::vec2 & minb, const glm::vec2 & maxb );

    glm::vec2 getMinBound() const;
    glm::vec2 getMaxBound() const;

private:
    glm::vec2 m_minb;
    glm::vec2 m_maxb;
};

//------------------------------------------------------------------------------
inline
WorldArea::WorldArea( const glm::vec2 & minb, const glm::vec2 & maxb ){
    m_minb = minb;
    m_maxb = maxb;
}

//------------------------------------------------------------------------------
inline
glm::vec2 WorldArea::getMinBound() const{
    return m_minb;
}

//------------------------------------------------------------------------------
inline
glm::vec2 WorldArea::getMaxBound() const{
    return m_maxb;
}

//------------------------------------------------------------------------------
#endif//WORLDAREA_HPP_

//------------------------------------------------------------------------------
