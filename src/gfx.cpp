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
#include "renderer.hpp"
#include "chunkprop.hpp"
#include "shader.hpp"
#include "terminal.hpp"
#include "staticmesh.hpp"
#include "material.hpp"
#include "engine.hpp"

//------------------------------------------------------------------------------
void Gfx::setup(){
    static_assert( DESIRED_HEIGHT > 0 and DESIRED_WIDTH > 0
                   , "Screen size must be > 0" );

    auto & engine = Engine::instance();

    sf::ContextSettings desired;
    desired.depthBits = 24;

    glGenVertexArrays( 1, &m_vertexArrayID );
    glBindVertexArray( m_vertexArrayID );

    m_window = new sf::RenderWindow{
        sf::VideoMode( DESIRED_WIDTH, DESIRED_HEIGHT ),
        "HexWorld", sf::Style::Default, desired };
    m_height = DESIRED_HEIGHT;
    m_width = DESIRED_WIDTH;
    m_guiView.setCenter( {DESIRED_WIDTH/2.0, DESIRED_HEIGHT/2.0} );
    m_guiView.setSize( {DESIRED_WIDTH, DESIRED_HEIGHT} );

    m_window->setVerticalSyncEnabled( true );
    m_window->setKeyRepeatEnabled( false );

    auto settings = m_window->getSettings();
    std::cout << "OpenGL version: " << settings.majorVersion << "."
              << settings.minorVersion << std::endl;

    clearModelStack();

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );

    // load texture
    auto tex_filename = engine.getDataFilename( "gfx/tile01.png" );
    m_tex_2d0 = SOIL_load_OGL_texture( tex_filename.data(),
                                       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                       SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
                                       | SOIL_FLAG_NTSC_SAFE_RGB
                                       | SOIL_FLAG_COMPRESS_TO_DXT );
    if( 0 == m_tex_2d0 ){
        std::cout << "SOIL loading error: '" << SOIL_last_result() << "'\n";
        std::cout << " at file " << tex_filename << "'\n";
        std::terminate();
    }

    tex_filename = engine.getDataFilename( "gfx/tile03.png" );
    m_tex_2d1 = SOIL_load_OGL_texture( tex_filename.data(),
                                       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                       SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
                                       | SOIL_FLAG_NTSC_SAFE_RGB
                                       | SOIL_FLAG_COMPRESS_TO_DXT );
    if( 0 == m_tex_2d1 ){
        std::cout << "SOIL loading error: '" << SOIL_last_result() << "'\n";
        std::cout << " at file " << tex_filename << "'\n";
        std::terminate();
    }

    glBindTexture( GL_TEXTURE_2D, m_tex_2d0 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glBindTexture( GL_TEXTURE_2D, 0 );

    glBindTexture( GL_TEXTURE_2D, m_tex_2d1 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glBindTexture( GL_TEXTURE_2D, 0 );

    m_chk_wall_prg = loadProgram( engine.getDataFilename( "shaders/chunk_wall" ) );
    m_chk_tile_prg = loadProgram( engine.getDataFilename( "shaders/chunk_tile" ) );
    m_chk_floor_prg = loadProgram( engine.getDataFilename( "shaders/chunk_floor" ) );

    m_objmat_prg = loadProgram( engine.getDataFilename( "shaders/objmat" ) );
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
        if( newFactor > 0 ){
            if( newFactor > SCR_FACTOR ){
                auto size = SCR_FACTOR/newFactor;
                auto offset = (1.0f - size) / 2.0f;
                m_guiView.setViewport( {offset, 0.0f, size , 1.0f } );
            }else{
                auto size = newFactor/SCR_FACTOR;
                auto offset = (1.0f - size) / 2.0f;
                m_guiView.setViewport( {0.0f, offset, 1.0f, size } );
            }

            m_window->setView( m_guiView );
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

