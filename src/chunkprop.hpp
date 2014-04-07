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
/** @file chunkprop.hpp
    @brief ChunkProp class declaration.
    @author Luis Cabellos
    @date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef CHUNKPROP_HPP_
#define CHUNKPROP_HPP_

//------------------------------------------------------------------------------
#include <array>
#include "constants.hpp"
#include "gfxinc.hpp"
#include "chunk.hpp"

//------------------------------------------------------------------------------
class Renderer;

//------------------------------------------------------------------------------
class ChunkProp{
public:
    static void setupCommon();

    ChunkProp();
    ChunkProp( const Chunk & chunk );
    void setup( const Chunk & chunk );
    void setPosition( const glm::vec3 & pos );
    const glm::vec3 & getPosition() const;

    void draw( Renderer & renderer );

    GLuint tileVertsBuff() const;
    GLuint tileUVBuff() const;
    GLuint tileTrisBuff() const;
    unsigned int tileTrisSize() const;
    const glm::vec3 & tilePos( unsigned int i ) const;

    GLuint faceVertsBuff() const;
    GLuint faceNormsBuff() const;
    GLuint faceUVBuff() const;
    GLuint faceTrisBuff() const;
    unsigned int faceTrisSize() const;

    GLuint floorVertsBuff() const;
    GLuint floorTrisBuff() const;
    unsigned int floorTrisSize() const;
    const glm::vec3 & floorPos() const;

private:
    constexpr static unsigned int TRIS_TILE = 4;
    constexpr static unsigned int FACES_TILE = 6;
    constexpr static unsigned int VERTS_FACE = 4;
    constexpr static unsigned int TRIS_FACE = 2;

    constexpr static unsigned int m_numFloorVerts =
        (Chunk::NTILES-1)*3;
    constexpr static unsigned int m_numFloorTris =
        (Chunk::NTILES-1)*2 + 4;
    constexpr static unsigned int m_numFaceVerts =
        Chunk::NTILES*FACES_TILE*VERTS_FACE;
    constexpr static unsigned int m_numFaceTris =
        Chunk::NTILES*FACES_TILE*TRIS_FACE;

    static std::array< GLuint, 2 > s_floorBuffers;
    static std::array< GLfloat, m_numFloorVerts*3 > s_floorVerts;
    static std::array< GLushort, m_numFloorTris*3 > s_floorTris;

    static std::array< GLuint, 3 > s_tileBuffers;
    static std::array< GLfloat, TILE_VERTICES*3 > s_tileVerts;
    static std::array< GLfloat, TILE_VERTICES*2 > s_tileUVs;
    static std::array< GLushort, TRIS_TILE*3 > s_tileTris;

    static std::array< GLushort, m_numFaceTris*3 > s_faceTris;
    static GLuint s_faceTrisBuffer;

    std::array< GLuint, 3 > m_faceBuffers;
    std::array< GLfloat, m_numFaceVerts*3 > m_faceVerts;
    std::array< GLfloat, m_numFaceVerts*3 > m_faceNorms;
    std::array< GLfloat, m_numFaceVerts*2 > m_faceUVs;

    std::array< glm::vec3, Chunk::NTILES > m_tilePos;
    glm::vec3 m_position;
    glm::vec3 m_floorPos;
};

//------------------------------------------------------------------------------
inline
void ChunkProp::setPosition( const glm::vec3 & pos ){
    m_position = pos;
}

//------------------------------------------------------------------------------
inline
const glm::vec3 & ChunkProp::getPosition() const{
    return m_position;
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::tileVertsBuff() const{
    return s_tileBuffers[0];
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::tileUVBuff() const{
    return s_tileBuffers[1];
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::tileTrisBuff() const{
    return s_tileBuffers[2];
}

//------------------------------------------------------------------------------
inline
unsigned int ChunkProp::tileTrisSize() const{
    return s_tileTris.size();
}

//------------------------------------------------------------------------------
inline
const glm::vec3 & ChunkProp::tilePos( unsigned int i ) const{
    return m_tilePos[i];
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::faceVertsBuff() const{
    return m_faceBuffers[0];
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::faceNormsBuff() const{
    return m_faceBuffers[1];
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::faceUVBuff() const{
    return m_faceBuffers[2];
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::faceTrisBuff() const{
    return s_faceTrisBuffer;
}

//------------------------------------------------------------------------------
inline
unsigned int ChunkProp::faceTrisSize() const{
    return s_faceTris.size();
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::floorVertsBuff() const{
    return s_floorBuffers[0];
}

//------------------------------------------------------------------------------
inline
GLuint ChunkProp::floorTrisBuff() const{
    return s_floorBuffers[1];
}

//------------------------------------------------------------------------------
inline
unsigned int ChunkProp::floorTrisSize() const{
    return s_floorTris.size();
}

//------------------------------------------------------------------------------
inline
const glm::vec3 & ChunkProp::floorPos() const{
    return m_floorPos;
}

//------------------------------------------------------------------------------
#endif//CHUNKPROP_HPP_

//------------------------------------------------------------------------------
