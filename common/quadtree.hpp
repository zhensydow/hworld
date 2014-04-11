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
    glm::vec2 m_center;
    glm::vec2 m_halfd;
};

//------------------------------------------------------------------------------
class QuadTree{
public:
    
private:
    
};

//------------------------------------------------------------------------------
#endif//QUADTREE_HPP_

//------------------------------------------------------------------------------
