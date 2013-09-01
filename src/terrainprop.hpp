/** @file terrainprop.hpp
     @brief TerrainProp declaration.
     @author Luis Cabellos
     @date 2013-09-01
 */
//------------------------------------------------------------------------------
#ifndef TERRAINPROP_HPP_
#define TERRAINPROP_HPP_

//------------------------------------------------------------------------------
class World;

//------------------------------------------------------------------------------
class TerrainProp{
public:
    TerrainProp( const World & world );

    void setFocus( unsigned int index );

private:
};

//------------------------------------------------------------------------------
#endif//TERRAINPROP_HPP_

//------------------------------------------------------------------------------
