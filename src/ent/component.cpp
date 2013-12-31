/** @file component.cpp
    @brief Component definitions.
    @author Luis Cabellos
    @date 2013-09-24
*/
//------------------------------------------------------------------------------
#include "component.hpp"

//------------------------------------------------------------------------------
Component::Component( Entity & e ) noexcept : m_entity(e) {
    //empty
}

//------------------------------------------------------------------------------
Component::~Component() {
    //empty
}

//------------------------------------------------------------------------------
lua_CFunction Component::getFunction( const std::string & name ) const{
    if( m_scriptTable ){
        auto it = m_scriptTable->find( name );
        if( it != m_scriptTable->end() ){
            return it->second;
        }
    }

    return nullptr;
}

//------------------------------------------------------------------------------
