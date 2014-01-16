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
