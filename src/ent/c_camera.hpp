//------------------------------------------------------------------------------
#ifndef C_CAMERA_HPP_
#define C_CAMERA_HPP_

//------------------------------------------------------------------------------
#include "component.hpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

//------------------------------------------------------------------------------
class CCamera : public Component {
public:
    constexpr static ComponentType type = ComponentType::CT_CAMERA;

    CCamera( Entity & e );

    ComponentType getType() const override;

    float getFov() const;
    void setFov( float f );

private:
    static Component::ScriptTable s_cameraTable;

    float m_fov {45.0f};
};

//------------------------------------------------------------------------------
inline
ComponentType CCamera::getType() const{
    return type;
}

//------------------------------------------------------------------------------
inline
float CCamera::getFov() const{
    return m_fov;
}

//------------------------------------------------------------------------------
inline
void CCamera::setFov( float f ){
    m_fov = f;
}

//------------------------------------------------------------------------------
#endif//C_CAMERA_HPP_

//------------------------------------------------------------------------------
