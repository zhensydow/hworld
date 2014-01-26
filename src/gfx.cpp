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
/** @file gfx.cpp
    @brief Gfx definitions.
    @author Luis Cabellos
    @date 2014-01-26
*/
//------------------------------------------------------------------------------
#include "gfx.hpp"
#include "renderer2d.hpp"
#include "renderer3d.hpp"

//------------------------------------------------------------------------------
void Gfx::setup(){
    static_assert( DESIRED_HEIGHT > 0 and DESIRED_WIDTH > 0
                   , "Screen size must be > 0" );

    sf::ContextSettings desired;
    desired.depthBits = 24;

    glGenVertexArrays( 1, &m_vertexArrayID );
    glBindVertexArray( m_vertexArrayID );

    m_window = new sf::RenderWindow{
        sf::VideoMode( DESIRED_WIDTH, DESIRED_HEIGHT ),
        "HexWorld", sf::Style::Default, desired };
    m_window->setVerticalSyncEnabled( true );
    m_window->setKeyRepeatEnabled( false );

    auto settings = m_window->getSettings();
    std::cout << "OpenGL version: " << settings.majorVersion << "."
              << settings.minorVersion << std::endl;

    m_renderer2D = std::make_shared<Renderer2D>( m_window );
    if( m_renderer2D ){
        auto & guiView = m_renderer2D->getGuiView();
        guiView.setCenter( {DESIRED_WIDTH/2.0, DESIRED_HEIGHT/2.0} );
        guiView.setSize( {DESIRED_WIDTH, DESIRED_HEIGHT} );
    }

    setViewport( DESIRED_WIDTH, DESIRED_HEIGHT );

    m_renderer3D = std::make_shared<Renderer3D>();
}

//------------------------------------------------------------------------------
void Gfx::destroy(){
    m_window->close();
}

//------------------------------------------------------------------------------
void Gfx::setViewport( GLsizei width, GLsizei height ){
    constexpr float SCR_FACTOR = float(DESIRED_WIDTH) / float(DESIRED_HEIGHT);
    static_assert( SCR_FACTOR > 0, "SCR_FACTOR must be > 0" );

    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);

    if( height > 0 ){
        auto newFactor = float(width)/float(height);
        if( newFactor > 0 and m_renderer2D ){
            auto & guiView = m_renderer2D->getGuiView();
            if( newFactor > SCR_FACTOR ){
                auto size = SCR_FACTOR/newFactor;
                auto offset = (1.0f - size) / 2.0f;
                guiView.setViewport( {offset, 0.0f, size , 1.0f } );
            }else{
                auto size = newFactor/SCR_FACTOR;
                auto offset = (1.0f - size) / 2.0f;
                guiView.setViewport( {0.0f, offset, 1.0f, size } );
            }
            m_renderer2D->resetGuiView();
        }
    }
}

//------------------------------------------------------------------------------
Ray Gfx::getMouseRay() const{
    auto viewport = getViewport();
    auto mpos = sf::Mouse::getPosition( *m_window );
    auto position = glm::vec3( mpos.x, viewport.z - mpos.y, 0.f );
    auto ray = Ray{};
    ray.origin = glm::unProject( position, view, proj, viewport );
    ray.direction = glm::unProject( glm::vec3( position.x, position.y, 1.0f ),
                                    view, proj, viewport );
    ray.direction = glm::normalize( ray.direction );
    return ray;
}

//------------------------------------------------------------------------------
void Gfx::startFrame() {
    m_currentRenderer = m_renderer3D;
    if( m_currentRenderer ){
        m_currentRenderer->clearModelStack();

        m_renderer3D->view = view;
        m_renderer3D->proj = proj;
        m_renderer3D->sundir = m_sundir;
    }

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//------------------------------------------------------------------------------
void Gfx::startGUI(){
    m_window->pushGLStates();
    m_currentRenderer = m_renderer2D;
}

//------------------------------------------------------------------------------
