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
/** @file quadnode.cpp
    @brief Quad Node Definitions.
    @author Luis Cabellos
    @date 2014-03-06
*/
//------------------------------------------------------------------------------
#include "quadnode.hpp"
#include <iostream>

//------------------------------------------------------------------------------
void QuadNode::setBound( glm::vec2 a, glm::vec2 b ){
    m_minbound = glm::vec2( std::min( a.x, b.x ), std::min( a.y, b.y ) );
    m_maxbound = glm::vec2( std::max( a.x, b.x ), std::max( a.y, b.y ) );
}

//------------------------------------------------------------------------------
void QuadNode::setChild( unsigned int idx, std::unique_ptr<QuadNode> && node ){
    if( idx < 4 ){
        m_children[idx] = std::move( node );
    }
}

//------------------------------------------------------------------------------
void QuadNode::printDebug( unsigned int n ){
    std::string tabs = "";

    for( unsigned i = 0 ; i < n ; ++i ){
        tabs += "  ";
    }

    std::cout << tabs << m_minbound.x << ", " << m_minbound.y << " -> "
              << m_maxbound.x << ", " << m_maxbound.y << std::endl;

    for( const auto & child: m_children ){
        if( child ){
            child->printDebug( n + 1 );
        }
    }
}

//------------------------------------------------------------------------------
