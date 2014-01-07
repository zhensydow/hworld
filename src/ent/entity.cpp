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
    std::cout << "entity " << this << std::endl;
    for( const auto & c: m_components ){
        std::cout << " + " << unsigned(c.first) << " "
                  << getComponentName(c.first) << " - "
                  << c.second << std::endl;
    }
}

//------------------------------------------------------------------------------
