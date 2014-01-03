/** @file staticmodel.hpp
    @brief StaticModel declarations.
    @author Luis Cabellos
    @date 2014-01-02
*/
//------------------------------------------------------------------------------
#ifndef STATICMODEL_HPP_
#define STATICMODEL_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include "staticmesh.hpp"

//------------------------------------------------------------------------------
class StaticModel {
public:
    void insertMesh( std::unique_ptr<StaticMesh> mesh );
    void draw( Renderer & renderer );

private:
    std::vector< std::unique_ptr<StaticMesh> > m_meshes;
};

//------------------------------------------------------------------------------
inline
void StaticModel::insertMesh( std::unique_ptr<StaticMesh> mesh ){
    if( mesh ){
        m_meshes.push_back( std::move(mesh) );
    }
}

//------------------------------------------------------------------------------
#endif//STATICMODEL_HPP_

//------------------------------------------------------------------------------
