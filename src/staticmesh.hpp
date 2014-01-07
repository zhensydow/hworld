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
class Material;

//------------------------------------------------------------------------------
class StaticMesh{
public:
    void setupGL();
    void draw( const Material & mat, Renderer & renderer );

    void reserveVertices( unsigned int num ) noexcept;
    void insertVertex( unsigned int num, glm::vec3 pos );

    void reserveTriangles( unsigned int num ) noexcept;
    void insertTriangle( unsigned int num, unsigned int a, unsigned int b, unsigned int c );

    void setMaterialIdx( unsigned int idx ) noexcept;
    unsigned int getMaterialIdx() const noexcept;

    GLuint vertsBuff() const;
    GLuint trisBuff() const;
    
    unsigned int trisSize() const;

private:
    std::array< GLuint, 2 > m_meshBuffers;
    std::vector< GLfloat > m_verts;
    std::vector< GLushort > m_tris;

    unsigned int m_materialIdx = 0;
};

//------------------------------------------------------------------------------
inline
void StaticMesh::reserveVertices( unsigned int num ) noexcept {
    m_verts.resize( 3*num );
}

//------------------------------------------------------------------------------
inline
void StaticMesh::reserveTriangles( unsigned int num ) noexcept {
    m_tris.resize( 3*num );
}

//------------------------------------------------------------------------------
inline
void StaticMesh::setMaterialIdx( unsigned int idx ) noexcept {
    m_materialIdx = idx;
}

//------------------------------------------------------------------------------
inline
unsigned int StaticMesh::getMaterialIdx() const noexcept {
    return m_materialIdx;
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
inline
void StaticMesh::insertTriangle( unsigned int num, unsigned int a, unsigned int b, unsigned int c ){
    auto idx = num*3;
    if( idx < (m_tris.size()-2) ){
        m_tris[ idx ] = a;
        m_tris[ idx + 1 ] = b;
        m_tris[ idx + 2 ] = c;
    }
}

//------------------------------------------------------------------------------
inline
GLuint StaticMesh::vertsBuff() const {
    return m_meshBuffers[0];
}

//------------------------------------------------------------------------------
inline
GLuint StaticMesh::trisBuff() const {
    return m_meshBuffers[1];
}

//------------------------------------------------------------------------------
inline
unsigned int StaticMesh::trisSize() const {
    return m_tris.size();
}

//------------------------------------------------------------------------------
#endif//STATICMESH_HPP_

//------------------------------------------------------------------------------
