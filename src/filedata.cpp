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
/** @file filedata.cpp
    @brief File Data definitions.
    @author Luis Cabellos
    @date 2013-09-22
*/
//------------------------------------------------------------------------------
#include "filedata.hpp"
#include <fstream>
#include "json/json.h"
#include "entity.hpp"
#include "engine.hpp"
#include "c_camera.hpp"
#include "c_transform.hpp"
#include "c_staticmodel.hpp"
#include "c_script.hpp"

//------------------------------------------------------------------------------
using namespace std;
using namespace boost::filesystem;

//------------------------------------------------------------------------------
void saveWorld( const World & /*world*/, const path & /*folder*/ ){
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
        cout << "ERROR: Unknown component in JSON '" << name << "'\n";
        return;
    }

    if( entity ){
        cfun->second( entity, data );
    }
}

//------------------------------------------------------------------------------
std::shared_ptr<Entity> makeEntity( const string  & filename ){
    if( !is_regular_file(filename) ){
        cout << "ERROR: Not file '" << filename << "'" << endl;
        return nullptr;
    }

    ifstream ifs( filename, ifstream::binary );
    if( !ifs ){
        cout << "ERROR: Could not open " << filename << endl;
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
        cout << "ERROR: invalid entity JSON parsing" << endl;
        cout << reader.getFormattedErrorMessages();
        return nullptr;
    }

    auto entity = std::make_shared<Entity>();
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
