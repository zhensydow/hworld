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
class CStaticModel : public Component, public IDrawable {
public:
    constexpr static ComponentType type = ComponentType::CT_STATICMODEL;

    CStaticModel( Entity & e );

    ComponentType getType() const override;

    void draw( Renderer & renderer ) override;

private:
};

//------------------------------------------------------------------------------
inline
ComponentType CStaticModel::getType() const{
    return type;
}

//------------------------------------------------------------------------------
#endif//C_STATICMODEL_HPP_

//------------------------------------------------------------------------------
