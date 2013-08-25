/** @file terminal.cpp
    @brief Terminal Singleton class.
    @author Luis Cabellos
    @date 2013-08-02
*/
//------------------------------------------------------------------------------
#include "terminal.hpp"
#include <iostream>
#include "renderer.hpp"

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
void Terminal::resize( const int x, const int y ){
    m_view.reset( sf::FloatRect( 0, 0, x, y ) );
    m_text.setPosition( 24, y - 24 );
}

//------------------------------------------------------------------------------
void Terminal::draw( Renderer & renderer ){
    renderer.render( *this );
}

//------------------------------------------------------------------------------
