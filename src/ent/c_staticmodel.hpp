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
/** @file c_staticmodel.hpp
    @brief StaticModel component declarations.
    @author Luis Cabellos
    @date 2014-01-02
*/
//------------------------------------------------------------------------------
#ifndef C_STATICMODEL_HPP_
#define C_STATICMODEL_HPP_

//------------------------------------------------------------------------------
#include "component.hpp"
#include "idrawable.hpp"

//------------------------------------------------------------------------------
class StaticModel;

//------------------------------------------------------------------------------
class CStaticModel : public Component, public IDrawable {
public:
    constexpr static ComponentType type = ComponentType::CT_STATICMODEL;

    CStaticModel( Entity & e );

    ComponentType getType() const override;

    void draw( Renderer & renderer ) override;

    void setModel( const std::string & name );

private:
    std::shared_ptr<StaticModel> m_model = nullptr;

};

//------------------------------------------------------------------------------
inline
ComponentType CStaticModel::getType() const{
    return type;
}

//------------------------------------------------------------------------------
#endif//C_STATICMODEL_HPP_

//------------------------------------------------------------------------------
