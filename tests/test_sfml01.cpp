/** @file test_sfml01.cpp
    @brief Test SFML + GL
    @author Luis Cabellos
    @date 2013-08-02
*/
//------------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

//------------------------------------------------------------------------------
/** Main program function.
   @returns the exit code of program.
 */
int main(){
    sf::RenderWindow window{ sf::VideoMode(800, 600), "Test SFML+GL" };

    bool running = true;
    while( running ){
        sf::Event event;
        while( window.pollEvent(event) ){
            if( event.type == sf::Event::Closed ){
                running = false;
            }else if(event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        window.display();
    }

    return 0;
}

//------------------------------------------------------------------------------
