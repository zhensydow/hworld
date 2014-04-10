How to                          {#howtopage}
======

Compile the project
-------------------

Compile with:
~~~~~~~~~~~~~~~~~~~~~
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/installpath/ ..
make
~~~~~~~~~~~~~~~~~~~~~

Compile debug:
~~~~~~~~~~~~~~~~~~~~~
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=RELWITHDEBINFO -DCMAKE_PREFIX_PATH=/installpath/ ..
make
~~~~~~~~~~~~~~~~~~~~~

Generate documentation:
~~~~~~~~~~~~~~~~~~~~~
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/installpath/ ..
make doc
~~~~~~~~~~~~~~~~~~~~~

Execute the tests
-----------------

Execute testing:
~~~~~~~~~~~~~~~~~~~~~
cd build
ctest
~~~~~~~~~~~~~~~~~~~~~

Check the available tests:
~~~~~~~~~~~~~~~~~~~~~
cd build
ctest -N
~~~~~~~~~~~~~~~~~~~~~

Execute only tests with 'string' in the name:
~~~~~~~~~~~~~~~~~~~~~
cd build
ctest -R string
~~~~~~~~~~~~~~~~~~~~~

Memory profiling
----------------

Check leaks and memory managment problems:
~~~~~~~~~~~~~~~~~~~~~
valgrind -v --leak-check=full --show-reachable=yes build/src/hworld
~~~~~~~~~~~~~~~~~~~~~

Profile the memory heap:
~~~~~~~~~~~~~~~~~~~~~
valgrind -v --tool=massif build/src/hworld
ms_print massif.out.*
massif-visualizer massif.out.*
~~~~~~~~~~~~~~~~~~~~~

Call profiling
--------------

~~~~~~~~~~~~~~~~~~~~~
valgrind --tool=callgrind src/hworld ../data/config.json
kcachegrind callgrind.out.*
~~~~~~~~~~~~~~~~~~~~~

When you want to profile only a part of the program, then start with profiling off and use CALLGRIND_TOGGLE_COLLECT to start to profile on the source:

~~~~~~~~~~~~~~~~~~~~~
#include <valgrind/callgrind.h>

void Engine::yield(){
    if( m_nextState ){
        CALLGRIND_TOGGLE_COLLECT;
        m_nextState->start();
        m_states.push( std::move(*m_nextState) );
        CALLGRIND_TOGGLE_COLLECT;
    }

    sf::sleep( sf::milliseconds(1) );
}
~~~~~~~~~~~~~~~~~~~~~

Compile and execute with:

~~~~~~~~~~~~~~~~~~~~~
valgrind --collect-at-start=no --tool=callgrind src/hworld ../data/config.json
kcachegrind callgrind.out.*
~~~~~~~~~~~~~~~~~~~~~

Also, you can have every detail on the memory behavior with:

~~~~~~~~~~~~~~~~~~~~~
valgrind --tool=callgrind  --simulate-cache=yes src/hworld ../data/config.json
kcachegrind callgrind.out.*
~~~~~~~~~~~~~~~~~~~~~

OpenGL profiling
----------------

~~~~~~~~~~~~~~~~~~~~~
apitrace trace --api gl src/hworld ../data/config.json
apitrace dump hworld.trace
qapitrace hworld.tracex
~~~~~~~~~~~~~~~~~~~~~

Static Code Analysis
--------------------

~~~~~~~~~~~~~~~~~~~~~
cppcheck commont src src/ent --enable=all -v -DGLM_FORCE_CXX11 | tee cppcheck.log
~~~~~~~~~~~~~~~~~~~~~

Export 3DS from blender
-----------------------

Forward: Z Forward
Up: Y Up

