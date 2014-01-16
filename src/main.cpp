/** @file main.cpp
    @brief Info
    @author Luis Cabellos
    @date 2013-07-24
*/
//------------------------------------------------------------------------------
#include <cstdlib>
#include "config.hpp"
#include "gfxinc.hpp"
#include "memory.hpp"
#include "filedata.hpp"
#include "engine.hpp"
#include "entity.hpp"

//------------------------------------------------------------------------------
/** Main program function.
   @returns the exit code of program.
 */
int main( int argc, char *argv[] ){
    if( argc != 2 ){
        std::cout << "usage: " << argv[0] << " <config filename>" << std::endl;
        return EXIT_FAILURE;
    }

    auto config = loadConfig( argv[1] );
    if( not config ){
        std::cout << "can't load config file" << std::endl;
        return EXIT_FAILURE;
    }

    outMemoryInfo();

    auto & engine = Engine::instance();
    engine.setup( *config );

    auto & world = engine.getWorld();
    auto & renderer = engine.getRenderer();
    auto & terminal = engine.getTerminal();

    auto window = renderer.getWindow();

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
        engine.draw();
        engine.yield();
    }

    engine.destroy();

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
