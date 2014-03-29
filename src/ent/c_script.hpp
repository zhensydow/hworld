/*------------------------------------------------------------------------------
    Copyright 2014, HexWorld Authors.

    This file is part of HexWorld.

    HexWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HexWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HexWorld.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------*/
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
#include "iupdate.hpp"

//------------------------------------------------------------------------------
class CScript : public Component, public IUpdate {
public:
    constexpr static ComponentType type = ComponentType::CT_SCRIPT;

    CScript( Entity & e );
    ~CScript();

    ComponentType getType() const override;

    void load( const std::string & filename );

    void update( double d ) override;

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
