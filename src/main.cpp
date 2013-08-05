
/** @file main.cpp
    @brief Info
    @author Luis Cabellos
    @date 2013-07-24
*/
//------------------------------------------------------------------------------
#include <iostream>
#include <SFML/Graphics.hpp>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "shader.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "SOIL.h"
#include "terminal.hpp"

//------------------------------------------------------------------------------
/** Main program function.
   @returns the exit code of program.
 */
int main(){
    sf::ContextSettings desired;
    desired.majorVersion = 3;
    desired.minorVersion = 3;

    GLuint vertexArrayID;
    glGenVertexArrays( 1, &vertexArrayID );
    glBindVertexArray( vertexArrayID );

    sf::RenderWindow window{
        sf::VideoMode(800, 600),
        "HexWorld", sf::Style::Default, desired };
    window.setVerticalSyncEnabled( true );

    auto settings = window.getSettings();

    Terminal terminal{ &window };
    terminal.initialize();

    std::cout << "depth bits: " << settings.depthBits << std::endl;
    std::cout << "stencil bits: " << settings.stencilBits << std::endl;
    std::cout << "antialiasing level: " << settings.antialiasingLevel << std::endl;
    std::cout << "version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LESS );
    glEnable( GL_CULL_FACE );

    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
       -1.0f, -1.0f, -1.0f,
       1.0f, -1.0f, -1.0f,
       0.0f,  1.0f, -1.0f,
       -1.0f, -1.0f, -3.0f,
       1.0f, -1.0f, -3.0f,
       0.0f,  1.0f, -3.0f,
    };

    static const GLfloat g_uv_buffer_data[] = {
        0.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
        0.0f,  0.0f,
        0.0f,  1.0f,
        1.0f,  1.0f,
    };

    static const GLushort g_index_data[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8,
    };

    // Generate buffers
    GLuint vertexbuffer, uvbuffer, elemBuffer;
    glGenBuffers( 1, &vertexbuffer );
    glGenBuffers( 1, &uvbuffer );
    glGenBuffers( 1, &elemBuffer );

    // load texture
    GLuint tex_2d = SOIL_load_OGL_texture( "data/img_cheryl.jpg",
                                           SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT );
    if( 0 == tex_2d ){
        std::cout << "SOIL loading error: '" << SOIL_last_result() << "'\n";
        std::terminate();
    }

    //put buffer data on OpenGL
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                  g_vertex_buffer_data, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, uvbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data),
                  g_uv_buffer_data, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elemBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(g_index_data),
                  g_index_data, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    GLuint programID = loadProgram( "test01" );

    float fov = 45.0;
    float px = 4;
    float py = 3;
    float pz = 3;

    auto matrix_id = glGetUniformLocation( programID , "MVP");
    auto texture_id = glGetUniformLocation( programID , "texSampler");
    glm::mat4 mvp, proj, view, model;

    bool running = true;
    while( running ){
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                running = false;
            }else if(event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
                terminal.resize();
            }
        }

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::U ) ){
            fov += 1;
            if( fov > 80.0 ){
                fov = 80.0;
            }
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::I ) ){
            fov -= 1;
            if( fov < 10.0 ){
                fov = 10.0;
            }
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ){
            px += 0.25;
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ){
            px -= 0.25;
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ){
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ){
                pz += 0.25;
            }else{
                py += 0.25;
            }
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ){
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ){
                pz -= 0.25;
            }else{
                py -= 0.25;
            }
        }

        view = glm::lookAt(
                           glm::vec3( px, py, pz ), // origing
                           glm::vec3(0,0,0), // looks to
                           glm::vec3(0,1,0)  // up
                           );
        proj = glm::perspective( fov, 4.0f / 3.0f, 0.1f, 100.0f );

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glUseProgram( programID );

        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, tex_2d );
        glUniform1i( texture_id, 0 );

        glEnableVertexAttribArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3, GL_FLOAT, GL_FALSE,  // size, type, normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray( 1 );
        glBindBuffer( GL_ARRAY_BUFFER, uvbuffer );
        glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elemBuffer );

        // Draw the triangles
        model = glm::mat4(1.0f);
        mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &mvp[0][0] );
        glDrawElements( GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, nullptr );

        model = glm::translate( 3.0f, 1.0f, 0.0f );
        mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &mvp[0][0] );
        glDrawElements( GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, nullptr );

        model = glm::translate(-3.0f, 0.0f, 0.0f) *
            glm::rotate( 45.0f, glm::vec3{1.0f, 0.0f, 0.0f} );
        mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &mvp[0][0] );
        glDrawElements( GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, nullptr);

        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        glBindTexture( GL_TEXTURE_2D, 0 );

        window.pushGLStates();

        terminal.draw();

        window.popGLStates();

        window.display();
    }

    return 0;
}

//------------------------------------------------------------------------------
