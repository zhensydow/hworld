/** @file entity.cpp
    @brief Entity definitions.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#include "entity.hpp"
#include "component.hpp"

//------------------------------------------------------------------------------
std::shared_ptr<Component> Entity::getComponent( ComponentType ct ){
    auto it = m_components.find( ct );

    if( it != m_components.end() ){
        return it->second;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
void Entity::insertComponent( std::shared_ptr<Component> c ){
    auto ct = c->getType();

    m_components[ ct ] = c;
}

//------------------------------------------------------------------------------
