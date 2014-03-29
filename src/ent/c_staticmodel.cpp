/*------------------------------------------------------------------------------
    Copyright 2014, HexWorld Authors.

    This file is part of HexWorld.

    HexWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HexWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HexWorld.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------*/
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
