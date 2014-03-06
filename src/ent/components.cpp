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
/** @file components.cpp
    @brief Components definitions.
    @author Luis Cabellos
    @date 2014-03-04
*/
//------------------------------------------------------------------------------
#include "components.hpp"
#include <unordered_map>
#include <algorithm>

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
static std::unordered_map< std::string, ComponentType > s_ctNames = {
    { "null", ComponentType::CT_NULL },
    { "transform", ComponentType::CT_TRANSFORM },
    { "staticmodel", ComponentType::CT_STATICMODEL },
    { "camera", ComponentType::CT_CAMERA },
    { "script", ComponentType::CT_SCRIPT },
};

//------------------------------------------------------------------------------
ComponentType getComponentType( const string & name ){
    auto it = s_ctNames.find( name );
    if( it != s_ctNames.end() ){
        return it->second;
    }

    return ComponentType::CT_INVALID;
}

//------------------------------------------------------------------------------
string getComponentName( ComponentType ct ){
    auto it = find_if( begin(s_ctNames), end( s_ctNames),
                       [ct](pair<string, ComponentType> val){
                           return val.second == ct;
                       } );
    if( it != end(s_ctNames) ){
        return it->first;
    }

    return "invalid";
}

//------------------------------------------------------------------------------
