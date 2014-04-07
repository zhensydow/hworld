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
/** @file constants.hpp
    @brief Constants values.
    @author Luis Cabellos
    @date 2014-04-05
*/
//------------------------------------------------------------------------------
#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <cmath>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

constexpr GLfloat PI = 3.14159265358979323846f;
constexpr GLfloat sqrt3 = std::sqrt( 3 );
constexpr GLfloat sixthPart = (60.0f * PI) / 180.0f; // 60 degrees

constexpr GLfloat TILE_RADIUS = 1.0f;
constexpr unsigned int TILE_VERTICES = 6;
constexpr GLfloat TILE_OFFSET_Y = sqrt3 * std::sqrt( TILE_RADIUS*TILE_RADIUS );

constexpr GLfloat CHUNK_OFFSET_X = 1.5f*TILE_RADIUS;
constexpr GLfloat CHUNK_OFFSET_Y = -2.5*TILE_OFFSET_Y;

//------------------------------------------------------------------------------
#endif//CONSTANTS_HPP_

//------------------------------------------------------------------------------
