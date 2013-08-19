/** @file main.cpp
    @brief Info
    @author Luis Cabellos
    @date 2013-07-24
*/
//------------------------------------------------------------------------------
#include "gfxinc.hpp"
#include "terminal.hpp"
#include "chunk.hpp"
#include "renderer.hpp"
#include "util.hpp"

//------------------------------------------------------------------------------
/** Main program function.
   @returns the exit code of program.
 */
int main(){
    Renderer renderer;

    renderer.setup();

    auto window = renderer.getWindow();

    Terminal terminal{ window };
    terminal.initialize();

    auto chunk = createRandomChunk( -5, 5 );
    auto cprop = createChunkProp( chunk );

    float fov = 45.0;
    float px = 4;
    float py = 3;
    float pz = 3;

    glm::mat4 proj, view, model;

    bool running = true;
    while( running ){
        sf::Event event;
        while( window->pollEvent(event) ){
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

        renderer.view = glm::lookAt(
                                    glm::vec3( px, py, pz ), // origing
                                    glm::vec3(0,0,0), // looks to
                                    glm::vec3(0,1,0)  // up
                                    );
        renderer.proj = glm::perspective( fov, 4.0f / 3.0f, 0.1f, 100.0f );

        renderer.startFrame();

        cprop.draw( renderer );

        window->pushGLStates();

        terminal.draw();

        window->popGLStates();

        window->display();
    }

    return 0;
}

//------------------------------------------------------------------------------
