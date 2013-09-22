/** @file memory.cpp
    @brief Memory util definitions.
    @author Luis Cabellos
    @date 2013-09-22
*/
//------------------------------------------------------------------------------
#include "chunk.hpp"
#include "chunkprop.hpp"
#include "terrainprop.hpp"
#include "world.hpp"

//------------------------------------------------------------------------------
void outMemoryInfo(){
    std::cout << "Chunk size: " << sizeof(Chunk) << std::endl;
    std::cout << "ChunkProp size: " << sizeof(ChunkProp) << std::endl;
    std::cout << "TerrainProp size: " << sizeof(TerrainProp) << std::endl;
    std::cout << "World size: " << sizeof(World) << std::endl;
}

//------------------------------------------------------------------------------
