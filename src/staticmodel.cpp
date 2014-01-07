/** @file staticmodel.cpp
    @brief StaticModel definitions.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#include "staticmodel.hpp"

//------------------------------------------------------------------------------
void StaticModel::insertNullMaterial(){
    Material mat;
    mat.setDiffuse( glm::vec3( 0.8, 0, 0.8 ) );
    insertMaterial( std::move(mat) );
}

//------------------------------------------------------------------------------
void StaticModel::draw( Renderer & renderer ){
    for( auto & mesh: m_meshes ){
        mesh->draw( renderer );
    }
}

//------------------------------------------------------------------------------
