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
/** @file renderer.hpp
    @brief Renderer declaration.
    @author Luis Cabellos
    @date 2013-08-19
*/
//------------------------------------------------------------------------------
#ifndef RENDERER_HPP_
#define RENDERER_HPP_

//------------------------------------------------------------------------------
#include <stack>
#include "gfxinc.hpp"

//------------------------------------------------------------------------------
class ChunkProp;
class Terminal;
class StaticMesh;
class Material;

//------------------------------------------------------------------------------
class Renderer {
public:
    virtual void render( const ChunkProp & chunkprop );
    virtual void render( const Terminal & terminal );
    virtual void render( const Material & material, const StaticMesh & mesh );

    void clearModelStack();
    void pushModel( const glm::mat4 & model );
    glm::mat4 & getModel();
    void popModel();

private:
    std::stack<glm::mat4> m_modelStack;

};

//------------------------------------------------------------------------------
inline
void Renderer::render( const ChunkProp & ){
    // empty
}

//------------------------------------------------------------------------------
inline
void Renderer::render( const Terminal & ){
    // empty
}

//------------------------------------------------------------------------------
inline
void Renderer::render( const Material &, const StaticMesh & ){
    // empty
}

//------------------------------------------------------------------------------
inline
glm::mat4 & Renderer::getModel(){
    return m_modelStack.top();
}

//------------------------------------------------------------------------------
inline
void Renderer::clearModelStack(){
    while( not m_modelStack.empty() ){
        m_modelStack.pop();
    }
    m_modelStack.emplace( glm::mat4(1.0f) );
}

//------------------------------------------------------------------------------
inline
void Renderer::popModel(){
    if( m_modelStack.size() > 1 ){
        m_modelStack.pop();
    }
}

//------------------------------------------------------------------------------
inline
void Renderer::pushModel( const glm::mat4 & mat ){
    m_modelStack.emplace( mat*getModel() );
}

//------------------------------------------------------------------------------
#endif//RENDERER_HPP_

//------------------------------------------------------------------------------
