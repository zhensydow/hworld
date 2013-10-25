/** @file component.hpp
    @brief Component Base Class Declaration.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include "lua.hpp"
#include "entity.hpp"

//------------------------------------------------------------------------------
class Component {
public:
    Component( Entity & e );
    virtual ~Component();

    virtual ComponentType getType() const = 0;

    Entity & getEntity();

    lua_CFunction getFunction( const std::string & name ) const;

protected:
    using ScriptTable = std::unordered_map< std::string, lua_CFunction>;
    void registerScripTable( std::shared_ptr<ScriptTable> table );

private:
    std::shared_ptr<ScriptTable> m_scriptTable = nullptr;

    Entity & m_entity;
};

//------------------------------------------------------------------------------
inline
Entity & Component::getEntity(){
    return m_entity;
}

//------------------------------------------------------------------------------
inline
bool hasComponent( Component & c, ComponentType ct ){
    return c.getEntity().hasComponent( ct );
}

//------------------------------------------------------------------------------
inline
void Component::registerScripTable( std::shared_ptr<Component::ScriptTable> table ){
    m_scriptTable = table;
}

//------------------------------------------------------------------------------
template<typename T>
inline
T & getComponent( Component & c, ComponentType ct ){
    return c.getEntity().getComponent<T>( ct );
}

//------------------------------------------------------------------------------
#endif//COMPONENT_HPP_

//------------------------------------------------------------------------------
