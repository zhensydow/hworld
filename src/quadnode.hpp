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
/** @file quadnode.hpp
    @brief Quad Node
    @author Luis Cabellos
    @date 2014-03-06
*/
//------------------------------------------------------------------------------
#ifndef QUADNODE_HPP_
#define QUADNODE_HPP_

//------------------------------------------------------------------------------
#include <array>
#include <vector>
#include <memory>
#include "types.hpp"
#include "glm/glm.hpp"

//------------------------------------------------------------------------------
class QuadNode {
public:
    glm::vec2 minBound() const;
    glm::vec2 maxBound() const;

    bool isLeaf() const;

    void setBound( glm::vec2 a, glm::vec2 b );
    void setChild( unsigned int idx, std::unique_ptr<QuadNode> && node );

    bool addChunk( ChunkID idx, const glm::vec2 & pos );

    void printDebug( unsigned int n = 0 );

private:
    glm::vec2 m_minbound;
    glm::vec2 m_maxbound;

    std::array<std::unique_ptr<QuadNode>, 4> m_children;

    std::vector<ChunkID> m_chunks;
};

//------------------------------------------------------------------------------
inline
glm::vec2 QuadNode::minBound() const{
    return m_minbound;
}

//------------------------------------------------------------------------------
inline
glm::vec2 QuadNode::maxBound() const{
    return m_maxbound;
}

//------------------------------------------------------------------------------
#endif//QUADNODE_HPP_

//------------------------------------------------------------------------------
