/** @file staticmesh.hpp
    @brief StaticMesh declaration.
    @author Luis Cabellos
    @date 2013-12-31
*/
//------------------------------------------------------------------------------
#ifndef STATICMESH_HPP_
#define STATICMESH_HPP_

//------------------------------------------------------------------------------
#include <vector>
#include "gfxinc.hpp"

//------------------------------------------------------------------------------
class Renderer;

//------------------------------------------------------------------------------
class StaticMesh{
public:
    void draw( Renderer & renderer );

private:
    std::vector< GLfloat > m_verts;
};

//------------------------------------------------------------------------------
#endif//STATICMESH_HPP_

//------------------------------------------------------------------------------
