/*
 * shader.hpp
 *
 *  Created on: 28/07/2013
 *      Author: cabellos
 */

#ifndef SHADER_HPP_
#define SHADER_HPP_

//------------------------------------------------------------------------------
#include <string>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

//------------------------------------------------------------------------------
GLuint loadProgram( const std::string &name );

//------------------------------------------------------------------------------
#endif /* SHADER_HPP_ */
