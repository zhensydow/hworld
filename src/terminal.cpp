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
/** @file terminal.cpp
    @brief Terminal Singleton class.
    @author Luis Cabellos
    @date 2013-08-02
*/
//------------------------------------------------------------------------------
#include "terminal.hpp"
#include <iostream>
#include "renderer.hpp"
#include "engine.hpp"

//------------------------------------------------------------------------------
void Terminal::initialize(){
    auto filename = Engine::instance().getDataFilename( "GentiumPlus-R.ttf" );
    if( !m_font.loadFromFile( filename ) ){
        std::cout << "Error loading Font\n";
        std::terminate();
    }

    m_texts.reserve( MAX_LINES );
    newLine( "Terminal Initialized" );
}

//------------------------------------------------------------------------------
void Terminal::resize( const unsigned int x, const unsigned int y ){
    m_view.reset( sf::FloatRect( 0, 0, x, y ) );
    m_height = y;
    updateLines();
}

//------------------------------------------------------------------------------
void Terminal::updateLines(){
    auto col = sf::Color::White;
    auto degradation = sf::Color( 230, 230, 230 );
    auto h = m_height - 2 * LINE_HEIGHT;
    for( auto t: m_texts ){
        t->setPosition( LINE_BORDER, h );
        t->setColor( col );
        h -= LINE_HEIGHT;
        col *= degradation;
    }
}

//------------------------------------------------------------------------------
std::shared_ptr<sf::Text> Terminal::makeLine(){
    if( m_texts.size() >= MAX_LINES ){
        m_texts.erase( m_texts.begin() + (MAX_LINES - 1), m_texts.end() );
    }

    auto t = m_texts.emplace( m_texts.begin(), new sf::Text() );
    (*t)->setFont( m_font );
    (*t)->setCharacterSize( LINE_SIZE );
    (*t)->setColor( sf::Color::White );

    updateLines();

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
    if( m_visible ){
        renderer.render( *this );
    }
}

//------------------------------------------------------------------------------
