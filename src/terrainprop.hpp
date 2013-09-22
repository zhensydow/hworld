/** @file terrainprop.hpp
     @brief TerrainProp declaration.
     @author Luis Cabellos
     @date 2013-09-01
 */
//------------------------------------------------------------------------------
#ifndef TERRAINPROP_HPP_
#define TERRAINPROP_HPP_

//------------------------------------------------------------------------------
#include <unordered_map>
#include <memory>

//------------------------------------------------------------------------------
class World;
class Renderer;
class ChunkProp;

//------------------------------------------------------------------------------
class TerrainProp{
public:
    TerrainProp( World & world );

    void setFocus( unsigned int index );

    void draw( Renderer & renderer );

private:
    World & m_world;

    std::unordered_map< unsigned int, std::shared_ptr< ChunkProp > > m_chunks;
};

//------------------------------------------------------------------------------
#endif//TERRAINPROP_HPP_

//------------------------------------------------------------------------------
