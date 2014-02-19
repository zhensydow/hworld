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

    void setParentPosition( const glm::vec3 & pos );
    void setPosition( const glm::vec3 & pos );
    glm::vec3 getGlobalPosition() const;

private:
    static Component::ScriptTable s_transformTable;

    glm::vec3 m_parentPos = glm::vec3( 0.0, 0.0, 0.0 );
    glm::vec3 m_pos = glm::vec3( 0.0, 0.0, 0.0 );
    glm::vec3 m_finalPos = glm::vec3( 0.0, 0.0, 0.0 );
    glm::vec3 m_rot;
};

//------------------------------------------------------------------------------
inline
ComponentType CTransform::getType() const{
    return type;
}

//------------------------------------------------------------------------------
inline
glm::vec3 CTransform::getGlobalPosition() const{
    return m_finalPos;
};

//------------------------------------------------------------------------------
inline
void CTransform::setPosition( const glm::vec3 & pos ){
    m_pos = pos;
    m_finalPos = m_pos + m_parentPos;
};

//------------------------------------------------------------------------------
inline
void CTransform::setParentPosition( const glm::vec3 & pos ){
    m_parentPos = pos;
    m_finalPos = m_pos + m_parentPos;
};

//------------------------------------------------------------------------------
#endif//C_TRANSFORM_HPP_

//------------------------------------------------------------------------------
