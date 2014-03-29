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
/** @file filedata.cpp
    @brief File Data definitions.
    @author Luis Cabellos
    @date 2013-09-22
*/
//------------------------------------------------------------------------------
#include "filedata.hpp"
#include <fstream>
#include "json/json.h"
#include "debug.hpp"
#include "entity.hpp"
#include "world.hpp"
#include "engine.hpp"
#include "c_camera.hpp"
#include "c_transform.hpp"
#include "c_staticmodel.hpp"
#include "c_script.hpp"

//------------------------------------------------------------------------------
using namespace std;
using namespace boost::filesystem;

//------------------------------------------------------------------------------
void saveWorld( const World & world, const path & folder ){
    logI( "saving the world ... " );

    auto & engine = Engine::instance();

    logI( " saving the terrain .. " );

    auto terrain_filename = path(folder) /= "terrain.dat";
    std::ofstream fterrain( engine.getDataFilename(terrain_filename),
                            std::ios::binary );

    if( not fterrain ){
        logE( "Can't open terrain file at: ", folder );
        return;
    }

    const auto & terrain = world.getTerrain();

    auto num_chunks = terrain.size();
    fterrain.write( reinterpret_cast<char *>(&num_chunks), sizeof( num_chunks ) );

    for( const auto & ci: terrain ){
        auto cid = ci.first;
        const auto & chunk = ci.second;
        fterrain.write( reinterpret_cast<const char *>(&cid), sizeof( cid ) );

        fterrain.write( reinterpret_cast<const char *>(&chunk.m_heights[0]),
                        chunk.m_heights.size()*sizeof(chunk.m_heights[0]) );

        fterrain.write( reinterpret_cast<const char *>(&chunk.m_tiles[0]),
                        chunk.m_tiles.size()*sizeof(chunk.m_tiles[0]) );

        fterrain.write( reinterpret_cast<const char *>(&chunk.m_neighbours[0]),
                        chunk.m_neighbours.size()*sizeof(chunk.m_neighbours[0]) );

        auto num_ents = chunk.m_entities.size();
        fterrain.write( reinterpret_cast<char *>(&num_ents),
                        sizeof( num_ents ) );
        for( const auto & ce: chunk.m_entities ){
            auto ent_tile = get<0>(ce);
            auto ent_id = get<1>(ce);
            fterrain.write( reinterpret_cast<const char *>(&ent_tile),
                            sizeof( ent_tile ) );
            fterrain.write( reinterpret_cast<const char *>(&ent_id),
                            sizeof( ent_id ) );
        }

        fterrain.write( reinterpret_cast<const char *>(&chunk.m_minNeighHeight),
                        sizeof(chunk.m_minNeighHeight) );
    }

    logI( ".. End saving" );
}

//------------------------------------------------------------------------------
void makeCCamera( shared_ptr<Entity> entity, const Json::Value & data){
    if( entity ){
        auto comp = getMakeComponent<CCamera>( *entity );

        if( data.isMember( "fov" ) ){
            auto & fovvalue = data["fov"];
            if( fovvalue.isNumeric() ){
                comp->setFov( fovvalue.asFloat() );
            }
        }
    }
}

//------------------------------------------------------------------------------
void makeCTransform( shared_ptr<Entity> entity, const Json::Value & data){
    if( entity ){
        auto comp = getMakeComponent<CTransform>( *entity );
        if( data.isMember( "pos" ) ){
            auto & filevalue = data["pos"];
            if( filevalue.isArray() ){
                glm::vec3 pos { 0.0f, 0.0f, 0.0f };
                auto size = filevalue.size();
                auto limit = std::min<decltype(size)>( 3, size );
                for( decltype(size) i = 0 ; i < limit ; ++i ){
                    auto & val = filevalue[i];
                    if( val.isNumeric() ){
                        pos[i] = val.asFloat();
                    }
                }

                comp->setPosition( pos );
            }
        }
    }
}

//------------------------------------------------------------------------------
void makeCStaticModel( shared_ptr<Entity> entity, const Json::Value & data){
    if( entity ){
        auto comp = getMakeComponent<CStaticModel>( *entity );
        if( data.isMember( "file" ) ){
            auto & filevalue = data["file"];
            if( filevalue.isString() ){
                comp->setModel( filevalue.asString() );
            }
        }
    }
}

//------------------------------------------------------------------------------
void makeCScript( shared_ptr<Entity> entity, const Json::Value & data){
    if( entity ){
        auto & engine = Engine::instance();
        auto comp = getMakeComponent<CScript>( *entity );

        if( data.isMember( "file" ) ){
            auto & filevalue = data["file"];
            if( filevalue.isString() ){
                auto filename = engine.getDataFilename( filevalue.asString() );
                comp->load( filename );
            }
        }
    }
}

//------------------------------------------------------------------------------
using MakeComponentFunction = void (*)( shared_ptr<Entity>, const Json::Value & );

//------------------------------------------------------------------------------
static unordered_map< string, MakeComponentFunction > s_componentTable =
    { {"camera", makeCCamera },
      {"staticmodel", makeCStaticModel },
      {"script", makeCScript },
      {"transform", makeCTransform } };

//------------------------------------------------------------------------------
void createComponent( shared_ptr<Entity> entity, const string & name,
                      const Json::Value & data )
{
    auto cfun = s_componentTable.find( name );

    if( cfun == s_componentTable.end() ){
        logE( "Unknown component in JSON '", name, "'" );
        return;
    }

    if( entity ){
        cfun->second( entity, data );
    }
}

//------------------------------------------------------------------------------
/** Create a new entity using the template data of a Json file.

    @param id id to set in new Entity
    @param filename file with Json data to create the entity
    @returns new entity created or nullptr
*/
std::shared_ptr<Entity> makeEntity( EntityID id, const string & filename ){
    if( id == ENTITY_NULL_IDX ){
        logE( "Bad Entity ID" );
        return nullptr;
    }

    if( !is_regular_file(filename) ){
        logE( "Not file '", filename, "'" );
        return nullptr;
    }

    ifstream ifs( filename, ifstream::binary );
    if( !ifs ){
        logE( "Could not open ", filename );
        return nullptr;
    }

    ifs.seekg( 0, ifs.end );
    auto length = ifs.tellg();
    ifs.seekg( 0, ifs.beg );

    string entityJson;
    entityJson.resize(length, ' ');
    auto begin = &*entityJson.begin();

    ifs.read( begin, length );
    ifs.close();

    Json::Value root;
    Json::Reader reader;

    auto parsingRet = reader.parse( entityJson, root );
    if( ! parsingRet ){
        logE( "Invalid entity JSON parsing : ",
              reader.getFormattedErrorMessages() );
        return nullptr;
    }

    auto entity = std::make_shared<Entity>( id );
    if( entity ){
        newComponent<CTransform>( *entity );

        auto comps = root.getMemberNames();

        for( const auto & name: comps ){
            auto & value = root[ name ];
            createComponent( entity, name, value );
        }
    }

    return entity;
}

//------------------------------------------------------------------------------
