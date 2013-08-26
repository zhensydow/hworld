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
    void resize( const unsigned int x, const unsigned int y );
    void draw( Renderer & renderer );

    void newLine( const std::string & line );
    void newLine( std::string && line );

    const sf::View & getView() const;
    const std::vector< std::shared_ptr<sf::Text> > & getTexts() const;

private:
    constexpr static unsigned int LINE_HEIGHT = 20;
    constexpr static unsigned int LINE_BORDER = 18;
    constexpr static unsigned int LINE_SIZE = 12;
    constexpr static unsigned int MAX_LINES = 15;

    std::shared_ptr<sf::Text> makeLine();
    void updateLines();

    std::vector< std::shared_ptr<sf::Text> > m_texts;
    sf::Font m_font;
    sf::View m_view;
    unsigned int m_height;
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
