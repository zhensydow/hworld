/** @file c_staticmodel.cpp
    @brief StaticModel Component definitions.
    @author Luis Cabellos
    @date 2014-01-02
*/
//------------------------------------------------------------------------------
#include "c_staticmodel.hpp"
#include "staticmodel.hpp"
#include "engine.hpp"
#include "c_transform.hpp"
#include "renderer.hpp"
#include "resourcefactory.hpp"

//------------------------------------------------------------------------------
constexpr ComponentType CStaticModel::type;

//------------------------------------------------------------------------------
CStaticModel::CStaticModel( Entity & e ) : Component( e ){
    // empty
}

//------------------------------------------------------------------------------
void CStaticModel::draw( Renderer & renderer ){
    if( m_model ){
        auto tcomp = getComponent<CTransform>( *this );
        if( tcomp ){
            renderer.pushModel( glm::translate( tcomp->getGlobalPosition() ) );
        }

        m_model->draw( renderer );

        if( tcomp ){
            renderer.popModel();
        }
    }
}

//------------------------------------------------------------------------------
void CStaticModel::setModel( const std::string & name ){
    auto & engine = Engine::instance();
    auto & resources = engine.getResourceFactory();
    m_model = resources.getSimpleModel( name );
}

//------------------------------------------------------------------------------
