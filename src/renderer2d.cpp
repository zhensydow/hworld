/*------------------------------------------------------------------------------
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
------------------------------------------------------------------------------*/
/** @file renderer2d.cpp
    @brief Renderer 2D definitions.
    @author Luis Cabellos
    @date 2014-01-26
*/
//------------------------------------------------------------------------------
#include "renderer2d.hpp"
#include "terminal.hpp"

//------------------------------------------------------------------------------
void Renderer2D::render( const Terminal & terminal ){
    m_window->setView( terminal.getView() );
    auto & texts = terminal.getTexts();
    for( const auto t: texts ){
        m_window->draw( (*t) );
    }
    m_window->setView( m_guiView );
}

//------------------------------------------------------------------------------
