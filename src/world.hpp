/** @file world.hpp
    @brief World Declaration.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#ifndef WORLD_HPP_
#define WORLD_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include "chunk.hpp"

//------------------------------------------------------------------------------
class World{
public:
    World();

    Chunk & getChunk( unsigned int );

private:
    std::unordered_map< unsigned int, Chunk>  m_terrain;
};

//------------------------------------------------------------------------------
#endif//WORLD_HPP_

//------------------------------------------------------------------------------
