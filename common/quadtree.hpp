/*------------------------------------------------------------------------------
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
------------------------------------------------------------------------------*/
/** @file quadtree.hpp
    @brief QuadTree
    @author Luis Cabellos
    @date 2014-04-11
*/
//------------------------------------------------------------------------------
#ifndef QUADTREE_HPP_
#define QUADTREE_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include <array>
#include "types.hpp"

//------------------------------------------------------------------------------
template<typename T>
class QuadPoint{
public:
    glm::vec2 m_pos;
    T m_val;
};

//------------------------------------------------------------------------------
class QuadAABB{
public:
    QuadAABB( const glm::vec2 & minb, const glm::vec2 & maxb );
    bool contains( const glm::vec2 & p ) const;

private:
    glm::vec2 m_center {0.0f, 0.0f};
    glm::vec2 m_halfd {0.0f, 0.0f};
};

//------------------------------------------------------------------------------
QuadAABB::QuadAABB( const glm::vec2 & minb, const glm::vec2 & maxb ){
    m_center = (maxb + minb) / 2.0f;
    m_halfd = maxb - m_center;
}

//------------------------------------------------------------------------------
bool QuadAABB::contains( const glm::vec2 & p ) const{
    if( ((m_center.x - m_halfd.x) > p.x) or 
        (p.x >= (m_center.x + m_halfd.x)) ){
        return false;
    }
    if( ((m_center.y - m_halfd.y) > p.y) or 
        (p.y >= (m_center.y + m_halfd.y)) ){
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
template<typename T>
class QuadTree{
public:
    QuadTree( const QuadAABB & bound );
    bool insert( glm::vec2 p, T val );

private:
    static constexpr unsigned int MAX_POINTS = 4;

    QuadAABB m_boundary;
    std::array<QuadPoint<T>, MAX_POINTS> m_points;
    unsigned int m_numpoints {0};

    std::array<std::unique_ptr< QuadTree<T> >, 4> m_quads;
};

//------------------------------------------------------------------------------
template<typename T>
QuadTree<T>::QuadTree( const QuadAABB & bound ) : m_boundary{ bound }{
    // empty
}

//------------------------------------------------------------------------------
template<typename T>
bool QuadTree<T>::insert( glm::vec2 p, T val ){
    // check if its inside bounds of quadtree
    if( not m_boundary.contains( p ) ){
        return false;
    }

    if( m_numpoints < MAX_POINTS ){
        std::cout << " inserted " << p.x << ", " << p.y << std::endl;
        QuadPoint<T> qp;
        qp.m_pos = p;
        qp.m_val = val;
        m_points[ m_numpoints ] = qp;
        ++m_numpoints;
        return true;
    }

    if( not m_quads[0] ){
    //     subdivide();
    }

    for( auto & qt: m_quads ){
        if( qt and qt->insert( p, val ) ){
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
#endif//QUADTREE_HPP_

//------------------------------------------------------------------------------
