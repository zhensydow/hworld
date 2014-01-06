/** @file c_staticmodel.cpp
    @brief StaticModel Component definitions.
    @author Luis Cabellos
    @date 2014-01-02
*/
//------------------------------------------------------------------------------
#include "c_staticmodel.hpp"
#include "staticmodel.hpp"
#include "engine.hpp"

//------------------------------------------------------------------------------
constexpr ComponentType CStaticModel::type;

//------------------------------------------------------------------------------
CStaticModel::CStaticModel( Entity & e ) : Component( e ){
    // empty
}

//------------------------------------------------------------------------------
void CStaticModel::draw( Renderer & renderer ){
    if( m_model ){
        m_model->draw( renderer );
    }
}

//------------------------------------------------------------------------------
void CStaticModel::setModel( const std::string & name ){
    auto & engine = Engine::instance();
    auto & resources = engine.getResourceFactory();
    m_model = resources.getSimpleModel( name );
}

//------------------------------------------------------------------------------
