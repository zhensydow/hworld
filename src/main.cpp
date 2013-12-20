/** @file main.cpp
    @brief Info
    @author Luis Cabellos
    @date 2013-07-24
*/
//------------------------------------------------------------------------------
#include "gfxinc.hpp"
#include "memory.hpp"
#include "filedata.hpp"
#include "engine.hpp"
#include "entity.hpp"
#include "c_transform.hpp"
#include "c_camera.hpp"
#include "c_script.hpp"

//------------------------------------------------------------------------------
/** Main program function.
   @returns the exit code of program.
 */
int main(){
    outMemoryInfo();

    auto & engine = Engine::instance();
    engine.setup();

    auto & world = engine.getWorld();
    auto & renderer = engine.getRenderer();
    auto & terminal = engine.getTerminal();

    auto window = renderer.getWindow();

    engine.setState( engine.makeGameState( "test" ) );

    auto camera = std::make_shared<Entity>();

    auto ctrans = newComponent<CTransform>( *camera );
    auto ccam = newComponent<CCamera>( *camera );
    auto cscr = newComponent<CScript>( *camera );

    cscr->load( engine.getDataFilename("simple_cam.lua") );

    engine.addEntity( camera );
    engine.setCamera( camera );

    bool test_flag = false;
    while( engine.isRunning() ){
        sf::Event event;
        while( window->pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                engine.stop();
            }else if( event.type == sf::Event::Resized ){
                renderer.setViewport( event.size.width, event.size.height );
                terminal.resize( event.size.width, event.size.height );
            }else if( event.type == sf::Event::KeyReleased ){
                if( event.key.code == sf::Keyboard::Tab ){
                    terminal.setVisible( not terminal.isVisible() );
                }else if( event.key.code == sf::Keyboard::S ){
                    terminal.newLine( "Saving..." );
                    saveWorld( world, "data" );
                }
            }
        }

        engine.update();

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) ){
            test_flag = not test_flag;
        }

        engine.draw();

        engine.yield();
    }

    return 0;
}

//------------------------------------------------------------------------------
