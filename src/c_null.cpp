/** @file c_null.cpp
    @brief Null Component Definition.
    @author Luis Cabellos
    @date 2013-10-13
*/
//-------------------------------------------------------------------------------
#include "c_null.hpp"
#include <iostream>

//-------------------------------------------------------------------------------
CNull::CNull( Entity & e ) : Component( e ){
    // empty
}

//-------------------------------------------------------------------------------
void CNull::test() const{
    std::cout << "Null Component test" << std::endl;
}

//-------------------------------------------------------------------------------
