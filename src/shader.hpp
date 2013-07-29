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
