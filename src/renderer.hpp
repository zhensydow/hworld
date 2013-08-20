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

//------------------------------------------------------------------------------
class ChunkProp;

//------------------------------------------------------------------------------
class Renderer {
public:
    void setup();
    void startFrame() const;
    void render( const ChunkProp & chunkprop );

    sf::RenderWindow * getWindow();

    glm::mat4 view;
    glm::mat4 proj;

private:
    sf::RenderWindow * m_window;

    glm::mat4 m_mvp;

    GLuint m_vertexArrayID;

    GLuint m_tex_2d0;
    GLuint m_tex_2d1;

    GLuint m_chunkprogram;
    GLuint m_chk_tile_prg;
    GLuint m_chk_floor_prg;
};

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
#endif//RENDERER_HPP_

//------------------------------------------------------------------------------
