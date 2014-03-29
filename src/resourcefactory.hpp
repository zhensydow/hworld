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
/** @file resourcefactory.hpp
    @brief ResourceFactory declarations.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#ifndef RESOURCEFACTORY_HPP_
#define RESOURCEFACTORY_HPP_

//------------------------------------------------------------------------------
#include <string>
#include <memory>
#include <unordered_map>

//------------------------------------------------------------------------------
class StaticModel;

//------------------------------------------------------------------------------
class ResourceFactory {
public:
    std::shared_ptr<StaticModel> getSimpleModel( const std::string & name );

private:
    std::unordered_map< std::string, std::shared_ptr<StaticModel> > m_modelMap;

};

//------------------------------------------------------------------------------
#endif//RESOURCEFACTORY_HPP_

//------------------------------------------------------------------------------
