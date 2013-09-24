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
#include "filedata.hpp"

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
    float dist = 7.0f;
    float angle1 = 0;
    float angle2 = 0;

    bool running = true;
    while( running ){
        sf::Event event;
        while( window->pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                running = false;
            }else if( event.type == sf::Event::Resized ){
                renderer.setViewport( event.size.width, event.size.height );
                terminal.resize( event.size.width, event.size.height );
            }else if( event.type == sf::Event::KeyReleased ){
                if( event.key.code == sf::Keyboard::Tab ){
                    terminal.setVisible( not terminal.isVisible() );
                }else if( event.key.code == sf::Keyboard::A ){
                    terminal.newLine( "Key A Pressed " );
                }else if( event.key.code == sf::Keyboard::B ){
                    terminal.newLine( "Key B is Pressed well" );
                }else if( event.key.code == sf::Keyboard::S ){
                    terminal.newLine( "Saving..." );
                    saveWorld( world, "data" );
                }else{
                    terminal.newLine( "Key Pressed " );
                }
            }
        }

        auto ray = renderer.getMouseRay();
        std::cout << ray.origin.x << ", " << ray.origin.y << ", "
                  << ray.origin.z << " -> ";
        std::cout << ray.direction.x << ", " << ray.direction.y << ", "
                  << ray.direction.z << std::endl;

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
            angle1 += 1.f;
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ){
            angle1 -= 1.f;
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ){
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ){
                dist += 0.25;
            }else{
                angle2 += 1.f;
            }
        }else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ){
            if( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ){
                dist -= 0.25;
            }else{
                angle2 -= 1.f;
            }
        }

        auto rot1 = glm::rotate( angle1, 0.0f, 1.0f, 0.0f );
        auto axis2 = rot1 * glm::vec4( 0.0f, 0.0f, -1.0f, 1.0f );
        auto vecx = glm::rotate( angle2, axis2.x, axis2.y, axis2.z )
            * rot1 * glm::vec4( dist, 0.0f, 0.0f, 0.0f );
        auto eye = glm::vec3( vecx.x, vecx.y, vecx.z );
        auto up = glm::cross( eye, glm::vec3( axis2.x, axis2.y, axis2.z ) );
        renderer.view = glm::lookAt( eye, glm::vec3(0,0,0), up );
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
