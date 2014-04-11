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
/** @file quadtree.cpp
    @brief QuadTree Class testing.
    @author Luis Cabellos
    @date 2014-04-11
*/
//------------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>
#include "quadtree.hpp"

//------------------------------------------------------------------------------
int main(){
    QuadTree<int> qt { QuadAABB{ {-0.001, -0.001}, {100.f, 100.f} } };

    if( not qt.insert( glm::vec2( 0.0, 0.0 ), 1 ) ){
        std::cout << " NOT inserted " << std::endl;
    }
    if( not qt.insert( glm::vec2( 0.0, 1.0 ), 2 ) ){
        std::cout << " NOT inserted " << std::endl;
    }
    if( not qt.insert( glm::vec2( 0.0, 1.0 ), 3 ) ){
        std::cout << " NOT inserted " << std::endl;
    }
    if( not qt.insert( glm::vec2( 0.0, 1.0 ), 4 ) ){
        std::cout << " NOT inserted " << std::endl;
    }
    if( not qt.insert( glm::vec2( 0.0, 1.7 ), 5 ) ){
        std::cout << " NOT inserted " << std::endl;
    }
    if( not qt.insert( glm::vec2( 2.0, 0.7 ), 6 ) ){
        std::cout << " NOT inserted " << std::endl;
    }

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
