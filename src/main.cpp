/** @file main.cpp
    @brief Info
    @author Luis Cabellos
    @date 2013-07-24
*/
//------------------------------------------------------------------------------
#include <cstdlib>
#include "config.hpp"
#include "memory.hpp"
#include "engine.hpp"

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
        std::cout << "can't load config file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    outMemoryInfo();

    auto & engine = Engine::instance();
    engine.setup( *config );

    while( engine.isRunning() ){
        engine.update();
        engine.draw();
        engine.yield();
    }

    engine.destroy();

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
