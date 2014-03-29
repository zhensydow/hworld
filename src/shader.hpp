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
/** @file shader.hpp
    @brief Shader util functions
    @author Luis Cabellos
    @date 2013-07-28
*/
//------------------------------------------------------------------------------
#ifndef SHADER_HPP_
#define SHADER_HPP_

//------------------------------------------------------------------------------
#include <string>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

//------------------------------------------------------------------------------
/** Load a GLSL program composed of a vertex shader and a fragment shader.
    @param name common file name of vertex/fragment shaders.
    @returns identifier of program.
 */
GLuint loadProgram( const std::string &name );

//------------------------------------------------------------------------------
#endif//SHADER_HPP_
