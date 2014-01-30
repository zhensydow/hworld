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
/** @file config.cpp
    @brief Configuration definitions.
    @author Luis Cabellos
    @date 2014-01-16
*/
//------------------------------------------------------------------------------
#include "config.hpp"
#include <boost/filesystem.hpp>
#include <fstream>
#include "json/json.h"

//------------------------------------------------------------------------------
using namespace std;
using namespace boost::filesystem;

//------------------------------------------------------------------------------
unique_ptr<Config> loadConfig( const string & filename ){
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

    auto config = unique_ptr<Config>( new Config );

    if( config ){
        config->datadir = path(filename).parent_path().string();

        if( root.isMember( "initialState" ) ){
            auto & value = root["initialState"];
            if( value.isString() ){
                config->initialState = value.asString();
            }
        }
    }

    return config;
}

//------------------------------------------------------------------------------
