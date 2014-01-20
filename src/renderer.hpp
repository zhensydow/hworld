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
#include "ray.hpp"

//------------------------------------------------------------------------------
class ChunkProp;
class Terminal;
class StaticMesh;
class Material;

//------------------------------------------------------------------------------
class Renderer {
public:
    void setup();
    void destroy();
    void startFrame() const;
    void startGUI();
    void endFrame();

    void setViewport( GLsizei width, GLsizei height );
    glm::vec4 getViewport() const;
    float aspectRatio() const;

    Ray getMouseRay() const;

    void render( const ChunkProp & chunkprop );
    void render( const Terminal & terminal );
    void render( const Material & material, const StaticMesh & mesh );

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
inline
float Renderer::aspectRatio() const {
    return m_width / m_height;
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
