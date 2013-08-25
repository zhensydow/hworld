/** @file renderer.cpp
    @brief Renderer Definition.
    @author Luis Cabellos
    @date 2013-08-19
*/
//------------------------------------------------------------------------------
#include "renderer.hpp"
#include "chunkprop.hpp"
#include "shader.hpp"
#include "terminal.hpp"

//------------------------------------------------------------------------------
void Renderer::setup(){
    sf::ContextSettings desired;
    desired.depthBits = 24;
    desired.majorVersion = 3;
    desired.minorVersion = 3;

    glGenVertexArrays( 1, &m_vertexArrayID );
    glBindVertexArray( m_vertexArrayID );

    m_window = new sf::RenderWindow{
        sf::VideoMode(800, 600),
        "HexWorld", sf::Style::Default, desired };

    m_window->setVerticalSyncEnabled( true );

    auto settings = m_window->getSettings();
    std::cout << "OpenGL version: " << settings.majorVersion << "."
              << settings.minorVersion << std::endl;

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );

    // load texture
    m_tex_2d0 = SOIL_load_OGL_texture( "data/tile01.png",
                                       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                       SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
                                       | SOIL_FLAG_NTSC_SAFE_RGB
                                       | SOIL_FLAG_COMPRESS_TO_DXT );
    if( 0 == m_tex_2d0 ){
        std::cout << "SOIL loading error: '" << SOIL_last_result() << "'\n";
        std::terminate();
    }

    m_tex_2d1 = SOIL_load_OGL_texture( "data/tile03.png",
                                       SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                       SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
                                       | SOIL_FLAG_NTSC_SAFE_RGB
                                       | SOIL_FLAG_COMPRESS_TO_DXT );
    if( 0 == m_tex_2d1 ){
        std::cout << "SOIL loading error: '" << SOIL_last_result() << "'\n";
        std::terminate();
    }

    glBindTexture( GL_TEXTURE_2D, m_tex_2d0 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glBindTexture( GL_TEXTURE_2D, 0 );

    glBindTexture( GL_TEXTURE_2D, m_tex_2d1 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glBindTexture( GL_TEXTURE_2D, 0 );

    m_chunkprogram = loadProgram( "test01" );
    m_chk_tile_prg = loadProgram( "chunk_tile" );
    m_chk_floor_prg = loadProgram( "chunk_floor" );
}

//------------------------------------------------------------------------------
void Renderer::render( const ChunkProp & chunkprop ){
    auto matrix_id = glGetUniformLocation( m_chk_tile_prg , "MVP");
    auto offset_id = glGetUniformLocation( m_chk_tile_prg , "offset");
    auto texture_id = glGetUniformLocation( m_chk_tile_prg , "texSampler");

    glUseProgram( m_chk_tile_prg );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_tex_2d0 );
    glUniform1i( texture_id, 0 );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.tileVertsBuff() );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.tileUVBuff() );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, chunkprop.tileTrisBuff() );

    auto model = glm::mat4(1.0f);

    for( unsigned i = 0 ; i < Chunk::NTILES ; ++i ){
        auto pos = chunkprop.tilePos( i );
        model = glm::translate( pos );
        m_mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
        glUniform2f( offset_id, pos.x, pos.z );
        glDrawElements( GL_TRIANGLES, chunkprop.tileTrisSize(),
                        GL_UNSIGNED_SHORT, nullptr);
    }

    matrix_id = glGetUniformLocation( m_chunkprogram , "MVP");
    texture_id = glGetUniformLocation( m_chunkprogram , "texSampler");
    glUseProgram( m_chunkprogram );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_tex_2d1 );

    glUniform1i( texture_id, 0 );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceVertsBuff() );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceUVBuff() );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, chunkprop.faceTrisBuff() );

    model = glm::mat4(1.0f);
    m_mvp = proj * view * model;
    glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
    glDrawElements( GL_TRIANGLES, chunkprop.faceTrisSize(),
                    GL_UNSIGNED_SHORT, nullptr);

    glActiveTexture( 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );

    matrix_id = glGetUniformLocation( m_chk_floor_prg, "MVP");

    glUseProgram( m_chk_floor_prg );

    model = glm::translate( chunkprop.floorPos() );
    m_mvp = proj * view * model;
    glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.floorVertsBuff() );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, chunkprop.floorTrisBuff() );

    glDrawElements( GL_TRIANGLES, chunkprop.floorTrisSize(),
                    GL_UNSIGNED_SHORT, nullptr);

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

//------------------------------------------------------------------------------
void Renderer::render( const Terminal & terminal ){
    m_window->setView( terminal.getView() );
    m_window->draw( terminal.getText() );
    m_window->setView( m_window->getDefaultView() );
}

//------------------------------------------------------------------------------
