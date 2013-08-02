/** @file terminal.hpp
    @brief Info
    @author Luis Cabellos
    @date 2013-08-02
*/
//------------------------------------------------------------------------------
#ifndef TERMINAL_HPP_
#define TERMINAL_HPP_

//------------------------------------------------------------------------------
#include <SFML/Graphics.hpp>

//------------------------------------------------------------------------------
class Terminal{
 public:
    explicit Terminal( sf::RenderWindow * window );
    void initialize();
    void resize();
    void draw();

 private:
    sf::RenderWindow * m_window;
    sf::Font m_font;
    sf::View m_view;
    sf::Text m_text;
};

//------------------------------------------------------------------------------
#endif//TERMINAL_HPP_
