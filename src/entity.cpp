/** @file entity.cpp
    @brief Entity definitions.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#include "entity.hpp"
#include <iostream>

//------------------------------------------------------------------------------
Entity::~Entity(){
    std::cout << "Entity " << m_id << "destroyed";
    m_components.clear();
}

//------------------------------------------------------------------------------
