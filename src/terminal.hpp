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

    bool isVisible() const;
    void setVisible( bool b );

    void newLine( const std::string & line );
    void newLine( std::string && line );

    const sf::View & getView() const;
    const std::vector< std::shared_ptr<sf::Text> > & getTexts() const;

private:
    constexpr static unsigned int LINE_HEIGHT = 16;
    constexpr static unsigned int LINE_BORDER = 18;
    constexpr static unsigned int LINE_SIZE = 12;
    constexpr static unsigned int MAX_LINES = 15;

    std::shared_ptr<sf::Text> makeLine();
    void updateLines();

    std::vector< std::shared_ptr<sf::Text> > m_texts;
    sf::Font m_font;
    sf::View m_view;
    unsigned int m_height;
    bool m_visible{ false };
};

//------------------------------------------------------------------------------
inline
bool Terminal::isVisible() const{
    return m_visible;
}

//------------------------------------------------------------------------------
inline
void Terminal::setVisible( bool b ){
    m_visible = b;
}

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
