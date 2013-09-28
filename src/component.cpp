/** @file component.cpp
    @brief Component definitions.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#include "component.hpp"
#include <iostream>

//------------------------------------------------------------------------------
Component::Component( std::shared_ptr<Entity> entity ) : m_entity( entity ){
    std::cout << "Component Created" << std::endl;
}

//------------------------------------------------------------------------------
Component::~Component(){
    std::cout << "Component Destroyed" << std::endl;    
}

//------------------------------------------------------------------------------
