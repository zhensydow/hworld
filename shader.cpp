/*
 * shader.cpp
 *
 *  Created on: 28/07/2013
 *      Author: cabellos
 */

#include "shader.hpp"

#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <fstream>

//------------------------------------------------------------------------------
void readFileData( const std::string &str, std::string &data ){
    std::ifstream t( str );

    if( t.good() ){
        t.seekg( 0, std::ios::end );
        data.reserve( t.tellg() );
        t.seekg( 0, std::ios::beg );

        data.assign( std::istreambuf_iterator<char>(t),
                     std::istreambuf_iterator<char>());
    }else{
        std::cerr << "File '" << str << "' doesn't exist\n";
        std::terminate();
    }
}

//------------------------------------------------------------------------------
GLuint createShader(GLenum shaderType, const std::string &filename ){
  GLuint shader = glCreateShader( shaderType );
  std::string filedata;
  readFileData( filename, filedata );
  const char *strFileData = filedata.c_str();
  glShaderSource( shader, 1, &strFileData, 0 );

  glCompileShader( shader );

  GLint status;
  glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
  if (status == GL_FALSE){
    GLint infoLogLength;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(shader, infoLogLength, 0, strInfoLog);

    const char *strShaderType = 0;
    switch( shaderType ){
    case GL_VERTEX_SHADER:
      strShaderType = "vertex";
      break;
    case GL_GEOMETRY_SHADER:
      strShaderType = "geometry";
      break;
    case GL_FRAGMENT_SHADER:
      strShaderType = "fragment";
      break;
    }

    std::cerr << "Compile failure in " << strShaderType << " shader: \n" << strInfoLog << std::endl;
    delete[] strInfoLog;
  }

  return shader;
}

//------------------------------------------------------------------------------
GLuint createProgram( const std::vector<GLuint> &shaders ){
  GLuint program = glCreateProgram();

  for( size_t i = 0; i < shaders.size(); i++ ){
    glAttachShader( program, shaders[i] );
  }

  glLinkProgram( program );

  GLint status;
  glGetProgramiv( program, GL_LINK_STATUS, &status );
  if( status == GL_FALSE ){
    GLint infoLogLength;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength );

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetProgramInfoLog( program, infoLogLength, 0, strInfoLog );
    std::cerr << "Linker failure: " << strInfoLog << std::endl;
    delete[] strInfoLog;
  }

  for( size_t i = 0; i < shaders.size(); i++ ){
    glDetachShader( program, shaders[i] );
  }

  return program;
}

//------------------------------------------------------------------------------
GLuint loadProgram( const std::string &name ){
    GLuint program{0};

    std::vector<GLuint> shaders;
    std::list<std::string> available = {"1.20","3.30"};

    std::string glslv;

    const GLubyte * glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    std::string sv(reinterpret_cast<const char*>(glslVersion));

    for( auto i = available.begin(); i != available.end() ; ++i ){
        if( 0 == sv.find(*i) ){
            glslv = *i;
            break;
        }
    }

    if( "" == glslv ){
        std::cout << "Invalid shader version: " << sv.c_str() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string strVertexShader = name+"."+glslv+".vert";
    std::string strFragmentShader = name+"."+glslv+".frag";

    shaders.push_back( createShader( GL_VERTEX_SHADER, strVertexShader ) );
    shaders.push_back( createShader( GL_FRAGMENT_SHADER, strFragmentShader ) );

    program = createProgram( shaders );

    std::for_each( shaders.begin(), shaders.end(), glDeleteShader );

    return program;
}

//------------------------------------------------------------------------------
