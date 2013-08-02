/** @file terminal.cpp
    @brief Terminal Singleton class.
    @author Luis Cabellos
    @date 2013-08-02
*/
//------------------------------------------------------------------------------
#include "terminal.hpp"
#include <iostream>

//------------------------------------------------------------------------------
Terminal::Terminal( sf::RenderWindow * window ) : m_window{ window } {
    // empty
}

//------------------------------------------------------------------------------
void Terminal::initialize(){
    if( !m_font.loadFromFile( "GentiumPlus-R.ttf") ){
        std::cout << "Error loading Font\n";
        std::terminate();
    }

    m_text.setFont( m_font );
    m_text.setString( "Hex World" );
    m_text.setCharacterSize( 12 );
    m_text.setColor( sf::Color::White );
}

//------------------------------------------------------------------------------
void Terminal::resize(){
    auto windowsize = m_window->getSize();
    m_view.reset( sf::FloatRect( 0, 0, windowsize.x, windowsize.y ) );
    m_text.setPosition( 24, windowsize.y - 24 );
}

//------------------------------------------------------------------------------
void Terminal::draw(){
    m_window->setView( m_view );
    m_window->draw( m_text );
    m_window->setView( m_window->getDefaultView() );
}

//------------------------------------------------------------------------------
