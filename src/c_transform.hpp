/** @file c_transform.hpp
    @brief Transform Component.
    @author Luis Cabellos
    @date 2013-10-20
*/
//------------------------------------------------------------------------------
#ifndef C_TRANSFORM_HPP_
#define C_TRANSFORM_HPP_

//------------------------------------------------------------------------------
#include "component.hpp"
#include "glm/glm.hpp"

//------------------------------------------------------------------------------
class CTransform : public Component {
public:
    constexpr static ComponentType type = ComponentType::CT_TRANSFORM;

    CTransform( Entity & e );

    ComponentType getType() const override;

private:
    glm::vec3 m_pos;
    glm::vec3 m_rot;
};

//------------------------------------------------------------------------------
inline
ComponentType CTransform::getType() const{
    return type;
}

//------------------------------------------------------------------------------
#endif//C_TRANSFORM_HPP_

//------------------------------------------------------------------------------
