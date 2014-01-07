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
    Component( Entity & e ) noexcept;
    virtual ~Component();

    virtual ComponentType getType() const = 0;

    Entity & getEntity();

    lua_CFunction getFunction( const std::string & name ) const;

protected:
    using ScriptTable = std::unordered_map< std::string, lua_CFunction>;
    void registerScriptTable( ScriptTable * table );

private:
    ScriptTable * m_scriptTable = nullptr;

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
void Component::registerScriptTable( Component::ScriptTable * table ){
    m_scriptTable = table;
}

//------------------------------------------------------------------------------
template<typename T>
inline
std::shared_ptr<T> getComponent( Component & c ){
    return c.getEntity().getComponent<T>();
}

//------------------------------------------------------------------------------
#endif//COMPONENT_HPP_

//------------------------------------------------------------------------------
