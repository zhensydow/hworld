//------------------------------------------------------------------------------
#ifndef C_CAMERA_HPP_
#define C_CAMERA_HPP_

//------------------------------------------------------------------------------
#include "component.hpp"

//------------------------------------------------------------------------------
class CCamera : public Component {
public:
    constexpr static ComponentType type = ComponentType::CT_CAMERA;

    CCamera( Entity & e );

    ComponentType getType() const override;

private:
};

//------------------------------------------------------------------------------
inline
ComponentType CCamera::getType() const{
    return type;
}

//------------------------------------------------------------------------------
#endif//C_CAMERA_HPP_

//------------------------------------------------------------------------------
