/** @file staticmodel.cpp
    @brief StaticModel definitions.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#include "staticmodel.hpp"

//------------------------------------------------------------------------------
void StaticModel::draw( Renderer & renderer ){
    for( auto & mesh: m_meshes ){
        mesh->draw( renderer );
    }
}

//------------------------------------------------------------------------------
