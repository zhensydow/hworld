/** @file renderer.hpp
    @brief Renderer declaration.
    @author Luis Cabellos
    @date 2013-08-19
*/
//------------------------------------------------------------------------------
#ifndef RENDERER_HPP_
#define RENDERER_HPP_

//------------------------------------------------------------------------------
#include "gfxinc.hpp"
#include "ray.hpp"

//------------------------------------------------------------------------------
class ChunkProp;
class Terminal;

//------------------------------------------------------------------------------
class Renderer {
public:
    void setup();
    void startFrame() const;
    void startGUI();
    void endFrame();

    void setViewport( GLsizei width, GLsizei height );
    glm::vec4 getViewport() const;

    Ray getMouseRay() const;

    void render( const ChunkProp & chunkprop );
    void render( const Terminal & terminal );

    sf::RenderWindow * getWindow();

    glm::mat4 view;
    glm::mat4 proj;

private:
    sf::RenderWindow * m_window;

    glm::mat4 m_mvp;

    float m_width;
    float m_height;

    GLuint m_vertexArrayID;

    GLuint m_tex_2d0;
    GLuint m_tex_2d1;

    GLuint m_chk_wall_prg;
    GLuint m_chk_tile_prg;
    GLuint m_chk_floor_prg;
};

//------------------------------------------------------------------------------
inline
void Renderer::setViewport( GLsizei width, GLsizei height ){
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}

//------------------------------------------------------------------------------
inline
glm::vec4 Renderer::getViewport() const {
    return glm::vec4( 0, 0, m_width, m_height );
}

//------------------------------------------------------------------------------
inline
sf::RenderWindow * Renderer::getWindow(){
    return m_window;
}

//------------------------------------------------------------------------------
inline
void Renderer::startFrame() const{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//------------------------------------------------------------------------------
inline
void Renderer::startGUI(){
    m_window->pushGLStates();
}

//------------------------------------------------------------------------------
inline
void Renderer::endFrame(){
    m_window->popGLStates();
    m_window->display();
}

//------------------------------------------------------------------------------
#endif//RENDERER_HPP_

//------------------------------------------------------------------------------
