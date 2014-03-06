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
/** @file c_camera.hpp
    @brief Camera Component Declaration.
    @author Luis Cabellos
    @date 2014-03-04
*/
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
