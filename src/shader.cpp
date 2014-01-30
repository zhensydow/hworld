/**
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
**/
/** @file shader.cpp
    @brief Shader utility functions.
    @author Luis Cabellos
    @date 2013-07-29
*/
//------------------------------------------------------------------------------
#include "shader.hpp"
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include "debug.hpp"

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
        logE( "File '", str, "' doesn't exist" );
        std::terminate();
    }
}

//------------------------------------------------------------------------------
GLuint createShader(GLenum shaderType, const std::string &filename ){
    auto shader = glCreateShader( shaderType );
    std::string filedata;
    readFileData( filename, filedata );
    auto strFileData = filedata.c_str();
    glShaderSource( shader, 1, &strFileData, 0 );

    glCompileShader( shader );

    GLint status;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
    if (status == GL_FALSE){
        GLint infoLogLength;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLength );

        auto strInfoLog = new GLchar[infoLogLength + 1];
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

        logE( "Compile failure in ", strShaderType, " shader:" );
        logE( "  ", filename );
        logE( strInfoLog );
        delete[] strInfoLog;
    }

    return shader;
}

//------------------------------------------------------------------------------
GLuint createProgram( const std::vector<GLuint> &shaders ){
    auto program = glCreateProgram();

    for( size_t i = 0; i < shaders.size(); i++ ){
        glAttachShader( program, shaders[i] );
    }

    glLinkProgram( program );

    GLint status;
    glGetProgramiv( program, GL_LINK_STATUS, &status );
    if( status == GL_FALSE ){
        GLint infoLogLength;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength );

        auto strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog( program, infoLogLength, 0, strInfoLog );
        logE( "Linker failure: ", strInfoLog );
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

    const auto glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    std::string sv( reinterpret_cast<const char*>(glslVersion) );

    for( auto i = available.begin(); i != available.end() ; ++i ){
        if( 0 == sv.find(*i) ){
            glslv = *i;
            break;
        }
    }

    if( "" == glslv ){
        logE( "Invalid shader version: ", sv.c_str() );
        std::terminate();
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
