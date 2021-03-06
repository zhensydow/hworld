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
/** @file components.hpp
    @brief Component Type enum.
    @author Luis Cabellos
    @date 2013-10-13
*/
//------------------------------------------------------------------------------
#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

//------------------------------------------------------------------------------
#include <string>

//------------------------------------------------------------------------------
enum class ComponentType{
    CT_INVALID,
    CT_NULL,
        CT_TRANSFORM,
        CT_STATICMODEL,
        CT_CAMERA,
        CT_SCRIPT
};

struct ComponentType_hash{
    template <typename T>
    inline
    typename std::enable_if<std::is_enum<T>::value, std::size_t>::type
    operator ()(T const value) const{
        return static_cast<std::size_t>(value);
    }
};

//------------------------------------------------------------------------------
ComponentType getComponentType( const std::string & name );
std::string getComponentName( ComponentType type );

//------------------------------------------------------------------------------
#endif//COMPONENTS_HPP_

//------------------------------------------------------------------------------
