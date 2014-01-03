/** @file resourcefactory.cpp
    @brief ResourceFactory definitions.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#include "resourcefactory.hpp"
#include "engine.hpp"
#include "gfxinc.hpp"
#include "staticmodel.hpp"

//------------------------------------------------------------------------------
using namespace std;

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
        auto scene = aiImportFile( engine.getDataFilename( name ).data(),
                                   aiProcess_CalcTangentSpace |
                                   aiProcess_Triangulate |
                                   aiProcess_JoinIdenticalVertices |
                                   aiProcess_SortByPType);

        if( !scene ){
            cout << "ERROR: " << aiGetErrorString() << endl;
        }else{
            for( unsigned i = 0 ; i < scene->mNumMeshes ; ++i ){
                auto mesh = unique_ptr<StaticMesh>( new StaticMesh() );
                auto aiMesh = scene->mMeshes[i];

                if( mesh ){
                    mesh->reserveVertices( aiMesh->mNumVertices );
                    for( unsigned i = 0 ; i < aiMesh->mNumVertices ; ++i ){
                        auto vertex = aiMesh->mVertices[i];
                        mesh->insertVertex( i,
                                            glm::vec3( vertex[0],
                                                       vertex[1],
                                                       vertex[2] ) );
                    }

                    mesh->reserveTriangles( aiMesh->mNumFaces );
                    for( unsigned i = 0 ; i < aiMesh->mNumFaces ; ++i ){
                        auto face = aiMesh->mFaces[i];
                        mesh->insertTriangle( i,
                                              face.mIndices[0],
                                              face.mIndices[1],
                                              face.mIndices[2] );
                    }

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
