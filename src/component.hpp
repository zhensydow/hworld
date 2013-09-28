/** @file component.hpp
    @brief Component Base Class Declaration.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

//------------------------------------------------------------------------------
#include <memory>

//------------------------------------------------------------------------------
class Entity;

//------------------------------------------------------------------------------
class Component{
public:
    Component( std::shared_ptr<Entity> entity );
    ~Component();

private:
    std::shared_ptr<Entity> m_entity;
};

//------------------------------------------------------------------------------
#endif//COMPONENT_HPP_

//------------------------------------------------------------------------------
