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
/** @file renderer.hpp
    @brief Renderer declaration.
    @author Luis Cabellos
    @date 2013-08-19
*/
//------------------------------------------------------------------------------
#ifndef RENDERER_HPP_
#define RENDERER_HPP_

//------------------------------------------------------------------------------
class ChunkProp;
class Terminal;
class StaticMesh;
class Material;

//------------------------------------------------------------------------------
class Renderer {
public:
    virtual void render( const ChunkProp & chunkprop ) = 0;
    virtual void render( const Terminal & terminal ) = 0;
    virtual void render( const Material & material, const StaticMesh & mesh ) = 0;

private:
};

//------------------------------------------------------------------------------
#endif//RENDERER_HPP_

//------------------------------------------------------------------------------
