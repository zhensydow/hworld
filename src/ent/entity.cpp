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
unsigned int Entity::s_lastID {ENTITY_NULL_ID};

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
