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
/** @file renderer2d.hpp
    @brief Renderer 2d for Gui.
    @author Luis Cabellos
    @date 2014-01-26
*/
//------------------------------------------------------------------------------
#ifndef RENDERER2D_HPP_
#define RENDERER2D_HPP_

//------------------------------------------------------------------------------
#include "renderer.hpp"
#include "gfxinc.hpp"

//------------------------------------------------------------------------------
class Renderer2D : public Renderer {
public:
    Renderer2D( sf::RenderWindow * window );

    sf::View & getGuiView();
    void resetGuiView();

    void render( const Terminal & terminal ) override;

private:
    sf::RenderWindow * m_window;
    sf::View m_guiView;

};

//------------------------------------------------------------------------------
inline
Renderer2D::Renderer2D( sf::RenderWindow * window ) : m_window(window) {
    // empty
}

//------------------------------------------------------------------------------
inline
sf::View & Renderer2D::getGuiView(){
    return m_guiView;
}

//------------------------------------------------------------------------------
inline
void Renderer2D::resetGuiView(){
    if( m_window ){
        m_window->setView( m_guiView );
    }
}

//------------------------------------------------------------------------------
#endif//RENDERER2D_HPP_

//------------------------------------------------------------------------------
