Hex World                         {#mainpage}
=========

Hex World Pet Project is a personal project to:

- refresh game programming
- refresh C++, learn C++11
- refresh OpenGL, learn Modern OpenGL
- have fun

![Terrain Demo](@ref shot01.png)

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

Libraries
---------

 * SFML 2.0 [www.sfml-dev.org](http://www.sfml-dev.org/index.php)
 * GLM 0.9.4 [glm.g-truc.net](http://glm.g-truc.net/api-0.9.4/index.html)
 * SOIL (Simple OpenGL Image Library) [lonesock.net](http://lonesock.net/soil.html)
 * jsoncpp [jsoncpp.sourceforge.net](http://jsoncpp.sourceforge.net)
 * LuaJIT [luajit.org](http://luajit.org)
 * Assimp [assimp.sourceforge.net](http://assimp.sourceforge.net/lib_html/index.html)

How to
------

 * Memory profiling

~~~~~~~~~~~~~~~~~~~~~
valgrind -v --leak-check=full --show-reachable=yes build/src/hworld
~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~
valgrind -v --tool=massif build/src/hworld
ms_print massif.out.*
massif-visualizer massif.out.*
~~~~~~~~~~~~~~~~~~~~~

 * Call profiling

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

 * OpenGL profiling

~~~~~~~~~~~~~~~~~~~~~
apitrace trace --api gl src/hworld ../data/config.json
apitrace dump hworld.trace
qapitrace hworld.tracex
~~~~~~~~~~~~~~~~~~~~~

 * Static Code Analysis

~~~~~~~~~~~~~~~~~~~~~
cppcheck src src/ent --enable=all -v -DGLM_FORCE_CXX11 | tee cppcheck.log
~~~~~~~~~~~~~~~~~~~~~

 * Export 3DS from blender

Forward: Z Forward
Up: Y Up

Other Resources
---------------

 * GentiumPlus [http://scripts.sil.org/cms/scripts/page.php?item_id=Gentium](http://scripts.sil.org/cms/scripts/page.php?item_id=Gentium)

Links
-----

 * [opengl tutorial](http://www.opengl-tutorial.org/)
 * [SFML 2.0 Documentation](http://www.sfml-dev.org/documentation/2.0/)
 * [Using OpenGL with SFML](http://www.sfml-dev.org/tutorials/2.0/window-opengl.php)
 * [Hexagonal Grids](http://www.redblobgames.com/grids/hexagons/)
 * [Entity Component Systems](http://entity-systems.wikidot.com/)
 * [Memory Debug](https://techtalk.intersec.com/2013/12/memory-part-5-debugging-tools/)
 * [Shadow Mapping](http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/)
 * [Polygonal Map Generation](http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/)
