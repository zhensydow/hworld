/** @file c_script.hpp
    @brief Script Component Declaration.
    @author Luis Cabellos
    @date 2013-10-22
*/
//------------------------------------------------------------------------------
#ifndef C_SCRIPT_HPP_
#define C_SCRIPT_HPP_

//------------------------------------------------------------------------------
#include "component.hpp"
#include "lua.hpp"

//------------------------------------------------------------------------------
class CScript : public Component {
public:
    constexpr static ComponentType type = ComponentType::CT_SCRIPT;

    CScript( Entity & e );

    ComponentType getType() const override;

    void load( const std::string & filename );

private:
    lua_State * m_lua = nullptr;
};

//------------------------------------------------------------------------------
inline
ComponentType CScript::getType() const{
    return type;
}

//------------------------------------------------------------------------------
#endif//C_SCRIPT_HPP_

//------------------------------------------------------------------------------
