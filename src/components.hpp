/** @file components.hpp
    @brief Component Type enum.
    @author Luis Cabellos
    @date 2013-10-13
*/
//------------------------------------------------------------------------------
#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

//------------------------------------------------------------------------------
#include <string>

//------------------------------------------------------------------------------
enum class ComponentType{
    CT_INVALID,
    CT_NULL,
        CT_TRANSFORM,
        CT_CAMERA,
        CT_SCRIPT
};

struct ComponentType_hash{
    template <typename T>
    inline
    typename std::enable_if<std::is_enum<T>::value, std::size_t>::type
    operator ()(T const value) const{
        return static_cast<std::size_t>(value);
    }
};

//------------------------------------------------------------------------------
ComponentType getComponentType( const std::string & name );

//------------------------------------------------------------------------------
#endif//COMPONENTS_HPP_

//------------------------------------------------------------------------------
