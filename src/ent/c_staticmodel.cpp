/** @file c_staticmodel.cpp
    @brief StaticModel Component definitions.
    @author Luis Cabellos
    @date 2014-01-02
*/
//------------------------------------------------------------------------------
#include "c_staticmodel.hpp"

//------------------------------------------------------------------------------
constexpr ComponentType CStaticModel::type;

//------------------------------------------------------------------------------
CStaticModel::CStaticModel( Entity & e ) : Component( e ){
    // empty
}

//------------------------------------------------------------------------------
void CStaticModel::draw( Renderer & renderer ){
}

//------------------------------------------------------------------------------
