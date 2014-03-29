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
/** @file entity.cpp
    @brief Entity definitions.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#include "entity.hpp"
#include <iostream>
#include "component.hpp"

//------------------------------------------------------------------------------
unsigned int Entity::s_lastID {ENTITY_NULL_IDX};

//------------------------------------------------------------------------------
bool Entity::hasComponent( ComponentType ct ) const{
    return m_components.find( ct ) != m_components.end();
}

//------------------------------------------------------------------------------
void Entity::insertComponent( std::shared_ptr<Component> c ){
    auto ct = c->getType();
    m_components[ ct ] = c;
}

//------------------------------------------------------------------------------
void Entity::printDebug() const{
    std::cout << "entity " << m_id << " " << this << std::endl;
    for( const auto & c: m_components ){
        std::cout << " + " << unsigned(c.first) << " "
                  << getComponentName(c.first) << " - "
                  << c.second << std::endl;
    }
}

//------------------------------------------------------------------------------
