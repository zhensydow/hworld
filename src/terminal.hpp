/** @file terminal.hpp
    @brief Info
    @author Luis Cabellos
    @date 2013-08-02
*/
//------------------------------------------------------------------------------
#ifndef TERMINAL_HPP_
#define TERMINAL_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include <SFML/Graphics.hpp>

//------------------------------------------------------------------------------
class Renderer;

//------------------------------------------------------------------------------
class Terminal{
public:
    void initialize();
    void resize( const int x, const int y );
    void draw( Renderer & renderer );

    void newLine( const std::string & line );
    void newLine( std::string && line );

    const sf::View & getView() const;
    const std::vector< std::shared_ptr<sf::Text> > & getTexts() const;

private:
    std::shared_ptr<sf::Text> makeLine();

    sf::Font m_font;
    sf::View m_view;

    std::vector< std::shared_ptr<sf::Text> > m_texts;
};

//------------------------------------------------------------------------------
inline
const sf::View & Terminal::getView() const{
    return m_view;
}

//------------------------------------------------------------------------------
inline
const std::vector< std::shared_ptr<sf::Text> > & Terminal::getTexts() const{
    return m_texts;
}

//------------------------------------------------------------------------------
#endif//TERMINAL_HPP_
