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
/** @file gfx.hpp
    @brief Graphics Class.
    @author Luis Cabellos
    @date 2014-01-26
*/
//------------------------------------------------------------------------------
#ifndef GFX_HPP_
#define GFX_HPP_

//------------------------------------------------------------------------------
#include <stack>
#include "gfxinc.hpp"
#include "ray.hpp"

//------------------------------------------------------------------------------
class ChunkProp;
class Terminal;
class StaticMesh;
class Material;

//------------------------------------------------------------------------------
class Gfx {
public:
    void setup();
    void destroy();
    void startFrame() const;
    void startGUI();
    void endFrame();

    void setSunDir( glm::vec3 && dir ) noexcept ;

    void setViewport( GLsizei width, GLsizei height );
    glm::vec4 getViewport() const;
    float aspectRatio() const;

    Ray getMouseRay() const;

    sf::RenderWindow * getWindow();

    void clearModelStack();
    void pushModel( const glm::mat4 & model );
    glm::mat4 & getModel();
    void popModel();

    glm::mat4 view;
    glm::mat4 proj;

private:
    constexpr static unsigned int DESIRED_WIDTH = 800;
    constexpr static unsigned int DESIRED_HEIGHT = 600;

    sf::RenderWindow * m_window;
    sf::View m_guiView;

    std::stack<glm::mat4> m_modelStack;

    glm::mat4 m_mvp;

    glm::vec3 m_sundir = glm::vec3( 0.0f, -1.0f, 0.0f );

    float m_width;
    float m_height;

    GLuint m_vertexArrayID;

    GLuint m_tex_2d0;
    GLuint m_tex_2d1;

    GLuint m_chk_wall_prg;
    GLuint m_chk_tile_prg;
    GLuint m_chk_floor_prg;

    GLuint m_objmat_prg;
};

//------------------------------------------------------------------------------
inline
void Gfx::startFrame() const{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//------------------------------------------------------------------------------
inline
void Gfx::startGUI(){
    m_window->pushGLStates();
}

//------------------------------------------------------------------------------
inline
void Gfx::endFrame(){
    m_window->popGLStates();
    m_window->display();
}

//------------------------------------------------------------------------------
inline
void Gfx::setSunDir( glm::vec3 && dir ) noexcept {
    if( glm::any( glm::notEqual( dir, glm::vec3(0.0f) ) ) ){
        m_sundir = std::move(dir);
    }
}

//------------------------------------------------------------------------------
inline
glm::mat4 & Gfx::getModel(){
    return m_modelStack.top();
}

//------------------------------------------------------------------------------
inline
void Gfx::clearModelStack(){
    while( not m_modelStack.empty() ){
        m_modelStack.pop();
    }
    m_modelStack.emplace( glm::mat4(1.0f) );
}

//------------------------------------------------------------------------------
inline
void Gfx::popModel(){
    if( m_modelStack.size() > 1 ){
        m_modelStack.pop();
    }
}

//------------------------------------------------------------------------------
inline
void Gfx::pushModel( const glm::mat4 & mat ){
    m_modelStack.emplace( mat*getModel() );
}

//------------------------------------------------------------------------------
inline
float Gfx::aspectRatio() const {
    return m_width / m_height;
}

//------------------------------------------------------------------------------
inline
glm::vec4 Gfx::getViewport() const {
    return glm::vec4( 0, 0, m_width, m_height );
}

//------------------------------------------------------------------------------
inline
sf::RenderWindow * Gfx::getWindow(){
    return m_window;
}

//------------------------------------------------------------------------------
#endif//GFX_HPP_

//------------------------------------------------------------------------------
