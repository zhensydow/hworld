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
/** @file debug.cpp
    @brief Debug functions definitions.
    @author Luis Cabellos
    @date 2014-01-29
*/
//------------------------------------------------------------------------------
#include "debug.hpp"
#include "chunk.hpp"
#include "chunkprop.hpp"
#include "terrainprop.hpp"
#include "world.hpp"

//------------------------------------------------------------------------------
static LogLevel s_loglevel = LogLevel::LL_ERROR;

static std::unordered_map<unsigned int,std::string> s_logNames = {
    {static_cast<unsigned int>(LogLevel::LL_ERROR), " [E] "},
    {static_cast<unsigned int>(LogLevel::LL_WARNING), " [W] "},
    {static_cast<unsigned int>(LogLevel::LL_INFO), " [I] "},
    {static_cast<unsigned int>(LogLevel::LL_DEBUG), " [D] "},
};

//------------------------------------------------------------------------------
void setLogLevel( LogLevel ll ){
    s_loglevel = ll;
}

//------------------------------------------------------------------------------
void printLogTag( LogLevel ll ){
    std::cout << s_logNames[static_cast<unsigned int>(ll)];
}

//------------------------------------------------------------------------------
bool logEnabled( LogLevel ll ){
    auto val_ll = static_cast<unsigned int>(ll);
    return val_ll <= static_cast<unsigned int>(s_loglevel);
}

//------------------------------------------------------------------------------
void outMemoryInfo(){
    std::cout << "Chunk size: " << sizeof(Chunk) << std::endl;
    std::cout << "ChunkProp size: " << sizeof(ChunkProp) << std::endl;
    std::cout << "TerrainProp size: " << sizeof(TerrainProp) << std::endl;
    std::cout << "World size: " << sizeof(World) << std::endl;
}

//------------------------------------------------------------------------------
