//------------------------------------------------------------------------------
#include "components.hpp"
#include <unordered_map>
#include <algorithm>

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
static std::unordered_map< std::string, ComponentType > s_ctNames = {
    { "null", ComponentType::CT_NULL },
    { "transform", ComponentType::CT_TRANSFORM },
    { "staticmodel", ComponentType::CT_STATICMODEL },
    { "camera", ComponentType::CT_CAMERA },
    { "script", ComponentType::CT_SCRIPT },
};

//------------------------------------------------------------------------------
ComponentType getComponentType( const string & name ){
    auto it = s_ctNames.find( name );
    if( it != s_ctNames.end() ){
        return it->second;
    }

    return ComponentType::CT_INVALID;
}

//------------------------------------------------------------------------------
string getComponentName( ComponentType ct ){
    auto it = find_if( begin(s_ctNames), end( s_ctNames),
                       [ct](pair<string, ComponentType> val){
                           return val.second == ct;
                       } );
    if( it != end(s_ctNames) ){
        return it->first;
    }

    return "invalid";
}

//------------------------------------------------------------------------------
