/**
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
**/
/** @file material.hpp
    @brief Material declarations.
    @author Luis Cabellos
    @date 2014-01-07
*/
//------------------------------------------------------------------------------
#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

//------------------------------------------------------------------------------
class Material{
public:
    void setDiffuse( const glm::vec3 & col ) noexcept;
    void setDiffuse( glm::vec3 && col ) noexcept;

    const glm::vec3 & getDiffuse() const noexcept;

private:
    glm::vec3 m_diffuse;
};

//------------------------------------------------------------------------------
inline
void Material::setDiffuse( const glm::vec3 & col ) noexcept {
    m_diffuse = col;
}

//------------------------------------------------------------------------------
inline
void Material::setDiffuse( glm::vec3 && col ) noexcept {
    m_diffuse = std::move(col);
}

//------------------------------------------------------------------------------
inline
const glm::vec3 & Material::getDiffuse() const noexcept {
    return m_diffuse;
}

//------------------------------------------------------------------------------
#endif//MATERIAL_HPP_

//------------------------------------------------------------------------------
