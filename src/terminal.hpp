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
class Renderer;

//------------------------------------------------------------------------------
class Terminal{
public:
    void initialize();
    void resize( const int x, const int y );
    void draw( Renderer & renderer );

    const sf::View & getView() const;
    const sf::Text & getText() const;

private:
    sf::Font m_font;
    sf::View m_view;
    sf::Text m_text;
};

//------------------------------------------------------------------------------
inline
const sf::View & Terminal::getView() const{
    return m_view;
}

//------------------------------------------------------------------------------
inline
const sf::Text & Terminal::getText() const{
    return m_text;
}

//------------------------------------------------------------------------------
#endif//TERMINAL_HPP_
