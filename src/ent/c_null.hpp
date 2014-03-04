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
/** @file c_null.hpp
    @brief Null Component.
    @author Luis Cabellos
    @date 2013-10-13
*/
//------------------------------------------------------------------------------
#ifndef C_NULL_HPP_
#define C_NULL_HPP_

//------------------------------------------------------------------------------
#include "component.hpp"

//------------------------------------------------------------------------------
class CNull : public Component {
public:
    constexpr static ComponentType type = ComponentType::CT_NULL;

    CNull( Entity & e );

    ComponentType getType() const override;

    void test() const;

private:
};

//------------------------------------------------------------------------------
inline
ComponentType CNull::getType() const{
    return type;
}

//------------------------------------------------------------------------------
#endif//C_NULL_HPP_

//------------------------------------------------------------------------------
