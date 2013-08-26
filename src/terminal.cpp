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

    newLine( "Terminal Initialized" );
}

//------------------------------------------------------------------------------
void Terminal::resize( const int x, const int y ){
    m_view.reset( sf::FloatRect( 0, 0, x, y ) );
    auto h = y - 24 * (1 + m_texts.size());
    for( auto t: m_texts ){
        t->setPosition( 24, h );
        h += 24;
    }
}

//------------------------------------------------------------------------------
std::shared_ptr<sf::Text> Terminal::makeLine(){
    auto t = m_texts.emplace( m_texts.begin(), new sf::Text() );
    (*t)->setFont( m_font );
    (*t)->setCharacterSize( 12 );
    (*t)->setColor( sf::Color::White );

    return (*t);
}

//------------------------------------------------------------------------------
void Terminal::newLine( const std::string & line ){
    auto t = makeLine();
    t->setString( line );
}

//------------------------------------------------------------------------------
void Terminal::newLine( std::string && line ){
    auto t = makeLine();
    t->setString( std::move(line) );
}

//------------------------------------------------------------------------------
void Terminal::draw( Renderer & renderer ){
    renderer.render( *this );
}

//------------------------------------------------------------------------------
