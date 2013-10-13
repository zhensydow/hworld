/** @file component.hpp
    @brief Component Base Class Declaration.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

//------------------------------------------------------------------------------
#include "entity.hpp"

//------------------------------------------------------------------------------
class Component {
public:
    Component( Entity & e );
    virtual ~Component();

    virtual ComponentType getType() const = 0;

    Entity & getEntity();

private:
    Entity & m_entity;
};

//------------------------------------------------------------------------------
inline
Entity & Component::getEntity(){
    return m_entity;
}

//------------------------------------------------------------------------------
inline
std::shared_ptr<Component> getComponent( Component & c, ComponentType ct ){
    return c.getEntity().getComponent( ct );
}

//------------------------------------------------------------------------------
#endif//COMPONENT_HPP_

//------------------------------------------------------------------------------
