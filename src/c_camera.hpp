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

    glm::mat4 getProjection() const;
    float getFov() const;
    void setFov( float f );
    void rotate_y( float angle );

private:
    float m_fov {45.0f};
};

//------------------------------------------------------------------------------
inline
ComponentType CCamera::getType() const{
    return type;
}

//------------------------------------------------------------------------------
inline
glm::mat4 CCamera::getProjection() const{
    return glm::perspective( m_fov, 4.0f / 3.0f, 0.1f, 100.0f );
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
