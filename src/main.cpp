/**
    Copyright 2014, HexWorld Authors.

    This file is part of HexWorld.

    HexWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HexWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HexWorld.  If not, see <http://www.gnu.org/licenses/>.
**/
/** @file main.cpp
    @brief Info
    @author Luis Cabellos
    @date 2013-07-24
*/
//------------------------------------------------------------------------------
#include <cstdlib>
#include "config.hpp"
#include "debug.hpp"
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
        logE( "Can't load config file ", argv[1] );
        return EXIT_FAILURE;
    }

    setLogLevel( config->loglevel );
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
