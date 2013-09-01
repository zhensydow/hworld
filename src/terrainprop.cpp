/** @file terrainprop.cpp
    @brief TerrainProp definition.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#include "terrainprop.hpp"
#include "chunkprop.hpp"

//------------------------------------------------------------------------------
TerrainProp::TerrainProp( const World & world ){
    ChunkProp::setupCommon();
}

//------------------------------------------------------------------------------
void TerrainProp::setFocus( unsigned int ){
}

//------------------------------------------------------------------------------
