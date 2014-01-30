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
static LogLevel s_loglevel = LogLevel::LL_INFO;

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
    time_t rawtime;
    tm * timeinfo;

    time( &rawtime );
    timeinfo = localtime( &rawtime );

    std::cout << timeinfo->tm_hour << ":"
              << timeinfo->tm_min << ":" << timeinfo->tm_sec
              << s_logNames[static_cast<unsigned int>(ll)];
}

//------------------------------------------------------------------------------
bool logEnabled( LogLevel ll ){
    return ll <= s_loglevel;
}

//------------------------------------------------------------------------------
void outMemoryInfo(){
    logI( "Chunk size: ", sizeof(Chunk) );
    logI( "ChunkProp size: ", sizeof(ChunkProp) );
    logI( "TerrainProp size: ", sizeof(TerrainProp) );
    logI( "World size: ", sizeof(World) );
}

//------------------------------------------------------------------------------
