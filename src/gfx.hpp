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
#include <memory>
#include <array>
#include "gfxinc.hpp"
#include "ray.hpp"

//------------------------------------------------------------------------------
class Config;
class Renderer;
class Renderer2D;
class Renderer3D;

//------------------------------------------------------------------------------
class Gfx {
public:
    void setup( const Config & config );
    void destroy();
    void startFrame();
    void startShadowMappingPass();
    void startColorPass();
    void startGUI();
    void endFrame();

    void enableRenderEffects( bool v = true ) noexcept;

    void setSunDir( glm::vec3 && dir ) noexcept ;

    void setViewport( GLsizei width, GLsizei height );
    glm::vec4 getViewport() const;
    float aspectRatio() const;

    Ray getMouseRay() const;

    sf::RenderWindow * getWindow();

    std::shared_ptr<Renderer> getCurrentRenderer() const;

    glm::mat4 view;
    glm::mat4 proj;

private:
    constexpr static unsigned int DESIRED_WIDTH = 800;
    constexpr static unsigned int DESIRED_HEIGHT = 600;

    void setGLSLVersion( const std::string & version );

    static std::array< GLfloat, 6*3 > s_quad_verts;

    sf::RenderWindow * m_window;

    glm::mat4 m_mvp;

    glm::vec3 m_sundir = glm::vec3( 0.0f, -1.0f, 0.0f );

    std::shared_ptr<Renderer> m_currentRenderer = nullptr;
    std::shared_ptr<Renderer2D> m_renderer2D = nullptr;
    std::shared_ptr<Renderer3D> m_renderer3D = nullptr;

    std::string m_glslVersion = "";

    float m_width;
    float m_height;

    GLuint m_vertexArrayID;
    GLuint m_fbRendered;
    GLuint m_renderedTex;
    GLuint m_renderedDepth;
    GLuint m_quad_prg;
    GLuint m_rfx_tex_id;
    GLuint m_rfx_time_id;
    GLuint m_rfx_w_id;
    GLuint m_rfx_h_id;
    GLuint m_quad_vertsbuff;

    bool m_rendereffects = false;
};

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
void Gfx::enableRenderEffects( bool v ) noexcept {
    m_rendereffects = v;
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
inline
std::shared_ptr<Renderer> Gfx::getCurrentRenderer() const {
    return m_currentRenderer;
}

//------------------------------------------------------------------------------
#endif//GFX_HPP_

//------------------------------------------------------------------------------
