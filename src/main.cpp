
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

    std::cout << "depth bits: " << settings.depthBits << std::endl;
    std::cout << "stencil bits: " << settings.stencilBits << std::endl;
    std::cout << "antialiasing level: " << settings.antialiasingLevel << std::endl;
    std::cout << "version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    sf::Font font;
    if( !font.loadFromFile( "GentiumPlus-R.ttf") ){
        std::cout << "Error loading Font\n";
        std::terminate();
    }

    sf::Text text;
    text.setFont( font );
    text.setString( "Hex World" );
    text.setCharacterSize( 18 );
    text.setColor( sf::Color::White );
    text.setStyle( sf::Text::Bold );

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

    static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
    };

    // This will identify our vertex buffer
    GLuint vertexbuffer, colorbuffer;

    // Generate buffers
    glGenBuffers( 1, &vertexbuffer );
    glGenBuffers( 1, &colorbuffer );

    //put buffer data on OpenGL
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                  g_vertex_buffer_data, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, colorbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
                  g_color_buffer_data, GL_STATIC_DRAW );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint programID = loadProgram( "test01" );

    float fov = 45.0;
    float px = 4;
    float py = 3;
    float pz = 3;

    // Camera matrix

    auto matrix_id = glGetUniformLocation( programID , "MVP");
    glm::mat4 mvp, proj, view, model;

    bool running = true;
    while( running ){
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                running = false;
            }else if(event.type == sf::Event::Resized){
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
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

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray( 1 );
        glBindBuffer( GL_ARRAY_BUFFER, colorbuffer );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE,
                               0, (void*)0 );

        // Draw the triangles
        model = glm::mat4(1.0f);
        mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &mvp[0][0] );
        glDrawArrays( GL_TRIANGLES, 0, 9 );

        model = glm::translate( 3.0f, 1.0f, 0.0f );
        mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &mvp[0][0] );
        glDrawArrays( GL_TRIANGLES, 0, 9 );

        model = glm::translate(-3.0f, 0.0f, 0.0f) *
            glm::rotate( 45.0f, glm::vec3{1.0f, 0.0f, 0.0f} );
        mvp = proj * view * model;
        glUniformMatrix4fv( matrix_id, 1, GL_FALSE, &mvp[0][0] );
        glDrawArrays( GL_TRIANGLES, 0, 9 );

        glDisableVertexAttribArray(0);
        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        window.pushGLStates();
        //window.resetGLStates();

        window.draw( text );

        window.popGLStates();

        window.display();
    }

    return 0;
}

//------------------------------------------------------------------------------
