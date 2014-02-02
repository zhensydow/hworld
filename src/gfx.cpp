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
#include "debug.hpp"
#include "config.hpp"
#include "engine.hpp"
#include "renderer2d.hpp"
#include "renderer3d.hpp"
#include "shader.hpp"

//------------------------------------------------------------------------------
std::array< GLfloat, 6*3 > Gfx::s_quad_verts = { {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
    } };

//------------------------------------------------------------------------------
void Gfx::setGLSLVersion( const std::string & version ){
}

//------------------------------------------------------------------------------
void Gfx::setup( const Config & config ){
    static_assert( DESIRED_HEIGHT > 0 and DESIRED_WIDTH > 0
                   , "Screen size must be > 0" );

    sf::ContextSettings desired;
    desired.depthBits = 24;

    glGenVertexArrays( 1, &m_vertexArrayID );
    glBindVertexArray( m_vertexArrayID );

    // rendered framebuffer values
    glGenFramebuffers( 1, &m_fbRendered );
    glGenTextures( 1, &m_renderedTex );
    glGenRenderbuffers( 1, &m_renderedDepth );

    m_window = new sf::RenderWindow{
        sf::VideoMode( DESIRED_WIDTH, DESIRED_HEIGHT ),
        "HexWorld", sf::Style::Default, desired };
    m_window->setVerticalSyncEnabled( true );
    m_window->setKeyRepeatEnabled( false );

    auto sets = m_window->getSettings();
    logI( "OpenGL version: ", sets.majorVersion, ".", sets.minorVersion );

    m_renderer2D = std::make_shared<Renderer2D>( m_window );
    if( m_renderer2D ){
        auto & guiView = m_renderer2D->getGuiView();
        guiView.setCenter( {DESIRED_WIDTH/2.0, DESIRED_HEIGHT/2.0} );
        guiView.setSize( {DESIRED_WIDTH, DESIRED_HEIGHT} );
    }

    setViewport( DESIRED_WIDTH, DESIRED_HEIGHT );

    m_renderer3D = std::make_shared<Renderer3D>();

    glGenBuffers( 1, &m_quad_vertsbuff );
    glBindBuffer( GL_ARRAY_BUFFER, m_quad_vertsbuff );
    glBufferData( GL_ARRAY_BUFFER, s_quad_verts.size()*sizeof(GLfloat),
                  &s_quad_verts[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    auto & engine = Engine::instance();
    m_quad_prg = loadProgram( engine.getDataFilename( "shaders/quad" ) );

    m_rfx_tex_id = glGetUniformLocation( m_quad_prg , "rendererTexture" );
    m_rfx_time_id = glGetUniformLocation( m_quad_prg , "time" );
    m_rfx_w_id = glGetUniformLocation( m_quad_prg , "width" );
    m_rfx_h_id = glGetUniformLocation( m_quad_prg , "height" );
}

//------------------------------------------------------------------------------
void Gfx::destroy(){
    m_window->close();
}

//------------------------------------------------------------------------------
void Gfx::setViewport( GLsizei width, GLsizei height ){
    constexpr float SCR_FACTOR = float(DESIRED_WIDTH) / float(DESIRED_HEIGHT);
    static_assert( SCR_FACTOR > 0, "SCR_FACTOR must be > 0" );
    logI( "Set Viewport to ", width, "x", height );

    m_width = width;
    m_height = height;

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

    // create the rendered framebuffer
    glBindFramebuffer( GL_FRAMEBUFFER, m_fbRendered );
    // setup the rendered texture
    glBindTexture( GL_TEXTURE_2D, m_renderedTex );
    glTexImage2D( GL_TEXTURE_2D, 0,GL_RGB, m_width, m_height, 0,
                  GL_RGB, GL_UNSIGNED_BYTE, 0 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    // setup the depth buffer
    glBindRenderbuffer( GL_RENDERBUFFER, m_renderedDepth );
    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height );
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                               GL_RENDERBUFFER, m_renderedDepth );
    //// Alternative : Depth texture. Slower, but you can sample it later in your shader
    // glBindTexture( GL_TEXTURE_2D, m_renderedDepthTex );
    // glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24,
    //              m_width, m_height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0 );
    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    // glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    // glFramebufferTexture( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_renderedDepthTex, 0 );
    // link with framebuffer
    glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderedTex, 0 );
    GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers( 1, DrawBuffers );

    // set shader constants
    glUseProgram( m_quad_prg );
    glUniform1f( m_rfx_w_id, m_width );
    glUniform1f( m_rfx_h_id, m_height );
    glUseProgram( 0 );

    auto ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if( ret != GL_FRAMEBUFFER_COMPLETE ){
        logW( "Can't generate Render FrameBuffer :", ret );
        std::terminate();
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
}

//------------------------------------------------------------------------------
void Gfx::startShadowMappingPass(){
    m_currentRenderer = nullptr;
}

//------------------------------------------------------------------------------
void Gfx::startColorPass(){
    m_currentRenderer = m_renderer3D;
    if( m_currentRenderer ){
        m_currentRenderer->clearModelStack();

        m_renderer3D->view = view;
        m_renderer3D->proj = proj;
        m_renderer3D->sundir = m_sundir;
    }

    if( m_rendereffects ){
        glBindFramebuffer( GL_FRAMEBUFFER, m_fbRendered );
    }else{
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    }
    glViewport( 0, 0, m_width, m_height );

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//------------------------------------------------------------------------------
void Gfx::startGUI(){
    if( m_rendereffects ){
        // render texture to screen
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
        glViewport( 0, 0, m_width, m_height );

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram( m_quad_prg );

        // Bind our texture in Texture Unit 0
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, m_renderedTex );
        glUniform1i( m_rfx_tex_id, 0 );
        auto & engine = Engine::instance();
        glUniform1f( m_rfx_time_id, static_cast<float>(engine.getTime()) );

        glEnableVertexAttribArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, m_quad_vertsbuff );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

        glDrawArrays( GL_TRIANGLES, 0, 6 );

        glDisableVertexAttribArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    m_window->pushGLStates();
    m_currentRenderer = m_renderer2D;
}

//------------------------------------------------------------------------------
