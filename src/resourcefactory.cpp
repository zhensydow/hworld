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
/** @file resourcefactory.cpp
    @brief ResourceFactory definitions.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#include "resourcefactory.hpp"
#include <boost/filesystem.hpp>
#include "engine.hpp"
#include "gfxinc.hpp"
#include "staticmodel.hpp"

//------------------------------------------------------------------------------
using namespace std;
using namespace boost::filesystem;

//------------------------------------------------------------------------------
shared_ptr<StaticModel> ResourceFactory::getSimpleModel( const string & name ){
    auto it = m_modelMap.find( name );
    if( it != m_modelMap.end() ){
        return it->second;
    }

    auto model = make_shared<StaticModel>();
    if( model ){
        m_modelMap[ name ] = model;

        auto & engine = Engine::instance();
        auto filename = engine.getDataFilename( path("gfx") /= name );
        auto scene = aiImportFile( filename.data(),
                                   aiProcess_GenNormals |
                                   aiProcess_Triangulate |
                                   aiProcess_JoinIdenticalVertices |
                                   aiProcess_OptimizeMeshes |
                                   aiProcess_SortByPType);

        if( !scene ){
            cout << "ERROR: " << aiGetErrorString() << endl;
        }else{
            for( unsigned i = 0 ; i < scene->mNumMaterials ; ++i ){
                Material material;
                auto aiMaterial = scene->mMaterials[i];

                aiColor3D difc( 0.0f, 0.0f, 0.0f );
                aiMaterial->Get( AI_MATKEY_COLOR_DIFFUSE, difc );
                material.setDiffuse( glm::vec3( difc.r, difc.g, difc.b) );

                model->insertMaterial( move(material) );
            }

            if( model->getNumMaterials() == 0 ){
                model->insertNullMaterial();
            }

            for( unsigned i = 0 ; i < scene->mNumMeshes ; ++i ){
                auto mesh = unique_ptr<StaticMesh>( new StaticMesh() );
                auto aiMesh = scene->mMeshes[i];

                if( mesh ){
                    mesh->reserveVertices( aiMesh->mNumVertices );
                    for( unsigned i = 0 ; i < aiMesh->mNumVertices ; ++i ){
                        auto vertex = aiMesh->mVertices[i];
                        auto normal = aiMesh->mNormals[i];
                        mesh->insertVertex( i,
                                            glm::vec3( vertex[0],
                                                       vertex[1],
                                                       vertex[2] ),
                                            glm::vec3( normal[0],
                                                       normal[1],
                                                       normal[2] ) );
                    }

                    mesh->reserveTriangles( aiMesh->mNumFaces );
                    for( unsigned i = 0 ; i < aiMesh->mNumFaces ; ++i ){
                        auto face = aiMesh->mFaces[i];
                        mesh->insertTriangle( i,
                                              face.mIndices[0],
                                              face.mIndices[1],
                                              face.mIndices[2] );
                    }

                    auto midx = min( model->getNumMaterials() - 1,
                                     aiMesh->mMaterialIndex );
                    mesh->setMaterialIdx( midx );

                    mesh->setupGL();

                    model->insertMesh( move(mesh) );
                }
            }

            aiReleaseImport( scene );
        }
    }

    return model;
}

//------------------------------------------------------------------------------
