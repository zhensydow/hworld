/**
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
**/
/** @file config.hpp
    @brief Configuration stuff.
    @author Luis Cabellos
    @date 2014-01-16
*/
//------------------------------------------------------------------------------
#ifndef CONFIG_HPP_
#define CONFIG_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include <string>
#include "debug.hpp"

//------------------------------------------------------------------------------
class Config{
public:
    std::string datadir = "";
    std::string initialState = "";
    LogLevel loglevel = LogLevel::LL_WARNING;
    std::string glslVersion = "";
};

//------------------------------------------------------------------------------
std::unique_ptr<Config> loadConfig( const std::string & filename );

//------------------------------------------------------------------------------
#endif//CONFIG_HPP_

//------------------------------------------------------------------------------
