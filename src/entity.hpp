/** @file entity.hpp
    @brief Entity Class Declaration.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#ifndef ENTITY_HPP_
#define ENTITY_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include <memory>
#include "components.hpp"

//------------------------------------------------------------------------------
class Component;

//------------------------------------------------------------------------------
class Entity final {
public:
    std::shared_ptr<Component> getComponent( ComponentType ct );
    void insertComponent( std::shared_ptr<Component> c );

private:
    std::unordered_map< ComponentType, std::shared_ptr<Component>, ComponentType_hash > m_components;
};

//------------------------------------------------------------------------------
#endif//ENTITY_HPP_

//------------------------------------------------------------------------------
