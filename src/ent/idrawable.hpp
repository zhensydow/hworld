/** @file idrawable.hpp
    @brief Drawable Interface for a component.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

//------------------------------------------------------------------------------
class Renderer;

//------------------------------------------------------------------------------
class IDrawable{
public:
    virtual void draw( Renderer & renderer ) = 0;
};

//------------------------------------------------------------------------------
#endif//IDRAWABLE_HPP_

//------------------------------------------------------------------------------