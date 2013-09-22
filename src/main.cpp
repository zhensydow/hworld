/** @file main.cpp
    @brief Info
    @author Luis Cabellos
    @date 2013-07-24
*/
//------------------------------------------------------------------------------
#include "gfxinc.hpp"
#include "terminal.hpp"
#include "renderer.hpp"
#include "world.hpp"
#include "terrainprop.hpp"
#include "memory.hpp"

//------------------------------------------------------------------------------
/** Main program function.
   @returns the exit code of program.
 */
int main(){
    outMemoryInfo();

    Renderer renderer;
    renderer.setup();

    Terminal terminal;
    terminal.initialize();

    World world;

    TerrainProp terrain( world );
    terrain.setFocus( 0 );

    auto window = renderer.getWindow();
    float fov = 45.0;
    float px = 4;
    float py = 3;
    float pz = 3;

    bool running = true;
    while( running ){
        sf::Event event;
        while( window->pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                running = false;
            }else if( event.type == sf::Event::Resized ){
                glViewport(0, 0, event.size.width, event.size.height);
                terminal.resize( event.size.width, event.size.height );
            }else if( event.type == sf::Event::KeyReleased ){
                if( event.key.code == sf::Keyboard::Tab ){
                    terminal.setVisible( not terminal.isVisible() );
                }else if( event.key.code == sf::Keyboard::A ){
                    terminal.newLine( "Key A Pressed " );
                }else if( event.key.code == sf::Keyboard::B ){
                    terminal.newLine( "Key B is Pressed well" );
                }else{
                    terminal.newLine( "Key Pressed " );
                }
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

        terrain.draw( renderer );

        renderer.startGUI();

        terminal.draw( renderer );

        renderer.endFrame();
    }

    return 0;
}

//------------------------------------------------------------------------------
