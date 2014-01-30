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
#include "staticmesh.hpp"
#include "material.hpp"
#include "engine.hpp"

//------------------------------------------------------------------------------
void Renderer::setViewport( GLsizei width, GLsizei height ){
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
Ray Renderer::getMouseRay() const{
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
void Renderer::setup(){
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
void Renderer::destroy(){
    m_window->close();
}

//------------------------------------------------------------------------------
void Renderer::render( const ChunkProp & chunkprop ){
    auto matrix_id = glGetUniformLocation( m_chk_tile_prg , "MVP");
    auto matrix_M_id = glGetUniformLocation( m_chk_tile_prg, "M");
    auto matrix_V_id = glGetUniformLocation( m_chk_tile_prg, "V");
    auto lightDir_id = glGetUniformLocation( m_chk_tile_prg, "lightDir");
    auto offset_id = glGetUniformLocation( m_chk_tile_prg , "offset");
    auto texture_id = glGetUniformLocation( m_chk_tile_prg , "texSampler");

    glUseProgram( m_chk_tile_prg );

    glUniform3fv( lightDir_id, 1, &m_sundir[0] );

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

    auto chunkPos = chunkprop.getPosition();
    auto model = glm::mat4(1.0f);

    glUniformMatrix4fv( matrix_V_id, 1, GL_FALSE, &view[0][0] );

    for( unsigned i = 0 ; i < Chunk::NTILES ; ++i ){
        auto pos = chunkprop.tilePos( i );
        model = glm::translate( pos + chunkPos );
        m_mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
        glUniformMatrix4fv( matrix_M_id, 1, GL_FALSE, &model[0][0] );
        glUniform2f( offset_id, pos.x, pos.z );
        glDrawElements( GL_TRIANGLES, chunkprop.tileTrisSize(),
                        GL_UNSIGNED_SHORT, nullptr);
    }

    matrix_id = glGetUniformLocation( m_chk_wall_prg, "MVP");
    matrix_M_id = glGetUniformLocation( m_chk_wall_prg, "M");
    matrix_V_id = glGetUniformLocation( m_chk_wall_prg, "V");
    lightDir_id = glGetUniformLocation( m_chk_wall_prg, "lightDir");
    texture_id = glGetUniformLocation( m_chk_wall_prg, "texSampler");
    glUseProgram( m_chk_wall_prg );

    glUniform3fv( lightDir_id, 1, &m_sundir[0] );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_tex_2d1 );

    glUniform1i( texture_id, 0 );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceVertsBuff() );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceUVBuff() );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 2 );
    glBindBuffer( GL_ARRAY_BUFFER, chunkprop.faceNormsBuff() );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, chunkprop.faceTrisBuff() );

    model = glm::translate( chunkPos );
    m_mvp = proj * view * model;
    glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
    glUniformMatrix4fv( matrix_M_id, 1, GL_FALSE, &model[0][0] );
    glUniformMatrix4fv( matrix_V_id, 1, GL_FALSE, &view[0][0] );
    glDrawElements( GL_TRIANGLES, chunkprop.faceTrisSize(),
                    GL_UNSIGNED_SHORT, nullptr);

    glDisableVertexAttribArray( 3 );
    glBindTexture( GL_TEXTURE_2D, 0 );

    matrix_id = glGetUniformLocation( m_chk_floor_prg, "MVP");

    glUseProgram( m_chk_floor_prg );

    model = glm::translate( chunkprop.floorPos() + chunkPos );
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
    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}

//------------------------------------------------------------------------------
void Renderer::render( const Terminal & terminal ){
    m_window->setView( terminal.getView() );
    auto texts = terminal.getTexts();
    for( const auto t: texts ){
        m_window->draw( (*t) );
    }
    m_window->setView( m_guiView );
}

//------------------------------------------------------------------------------
void Renderer::render( const Material & material, const StaticMesh & mesh ){
    auto matrix_id = glGetUniformLocation( m_objmat_prg, "MVP");
    auto matrix_M_id = glGetUniformLocation( m_objmat_prg, "M");
    auto matrix_V_id = glGetUniformLocation( m_objmat_prg, "V");
    auto diffuse_id = glGetUniformLocation( m_objmat_prg, "diffuse");
    auto lightDir_id = glGetUniformLocation( m_objmat_prg, "lightDir");

    glUseProgram( m_objmat_prg );

    const auto & difc = material.getDiffuse();
    glUniform3fv( diffuse_id, 1, &difc[0] );
    glUniform3fv( lightDir_id, 1, &m_sundir[0] );

    auto & mod = getModel();
    m_mvp = proj * view * mod;
    glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &m_mvp[0][0] );
    glUniformMatrix4fv( matrix_M_id, 1, GL_FALSE, &mod[0][0] );
    glUniformMatrix4fv( matrix_V_id, 1, GL_FALSE, &view[0][0] );

    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, mesh.vertsBuff() );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, mesh.normalsBuff() );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.trisBuff() );

    glDrawElements( GL_TRIANGLES, mesh.trisSize(),
                    GL_UNSIGNED_SHORT, nullptr);

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}

//------------------------------------------------------------------------------
