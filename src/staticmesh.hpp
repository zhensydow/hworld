/** @file staticmesh.hpp
    @brief StaticMesh declaration.
    @author Luis Cabellos
    @date 2013-12-31
*/
//------------------------------------------------------------------------------
#ifndef STATICMESH_HPP_
#define STATICMESH_HPP_

//------------------------------------------------------------------------------
#include <array>
#include <vector>
#include "gfxinc.hpp"

//------------------------------------------------------------------------------
class Renderer;

//------------------------------------------------------------------------------
class StaticMesh{
public:
    void setupGL();
    void draw( Renderer & renderer );

    void reserveVertices( unsigned int num ) noexcept;
    void insertVertex( unsigned int num, glm::vec3 pos );

private:
    std::array< GLuint, 1 > m_meshBuffers;
    std::vector< GLfloat > m_verts;
};

//------------------------------------------------------------------------------
inline
void StaticMesh::reserveVertices( unsigned int num ) noexcept {
    m_verts.reserve( 3*num );
}

//------------------------------------------------------------------------------
inline
void StaticMesh::insertVertex( unsigned int num, glm::vec3 pos ){
    auto idx = num*3;
    if( idx < (m_verts.size()-2) ){
        m_verts[ idx ] = pos[0];
        m_verts[ idx + 1 ] = pos[1];
        m_verts[ idx + 2 ] = pos[2];
    }
}

//------------------------------------------------------------------------------
#endif//STATICMESH_HPP_

//------------------------------------------------------------------------------
