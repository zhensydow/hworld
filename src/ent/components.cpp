//------------------------------------------------------------------------------
#include "components.hpp"
#include <unordered_map>

//------------------------------------------------------------------------------
static std::unordered_map< std::string, ComponentType > s_ctNames = {
    { "null", ComponentType::CT_NULL },
    { "transform", ComponentType::CT_TRANSFORM },
    { "staticmodel", ComponentType::CT_STATICMODEL },
    { "camera", ComponentType::CT_CAMERA },
    { "script", ComponentType::CT_SCRIPT },
};

//------------------------------------------------------------------------------
ComponentType getComponentType( const std::string & name ){
    auto it = s_ctNames.find( name );
    if( it != s_ctNames.end() ){
        return it->second;
    }

    return ComponentType::CT_INVALID;
}

//------------------------------------------------------------------------------
