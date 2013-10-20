/** @file components.hpp
    @brief Component Type enum.
    @author Luis Cabellos
    @date 2013-10-13
*/
//------------------------------------------------------------------------------
#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

enum class ComponentType{
    CT_NULL,
        CT_TRANSFORM,
        CT_CAMERA
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
#endif//COMPONENTS_HPP_

//------------------------------------------------------------------------------
