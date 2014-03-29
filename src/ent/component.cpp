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
/** @file component.cpp
    @brief Component definitions.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#include "component.hpp"

//------------------------------------------------------------------------------
Component::Component( Entity & e ) noexcept : m_entity(e) {
    //empty
}

//------------------------------------------------------------------------------
Component::~Component() {
    //empty
}

//------------------------------------------------------------------------------
lua_CFunction Component::getFunction( const std::string & name ) const{
    if( m_scriptTable ){
        auto it = m_scriptTable->find( name );
        if( it != m_scriptTable->end() ){
            return it->second;
        }
    }

    return nullptr;
}

//------------------------------------------------------------------------------
