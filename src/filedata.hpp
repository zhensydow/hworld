/** @file filedata.hpp
    @brief File Data functions.
    @author Luis Cabellos
    @date 2013-09-22
*/

//------------------------------------------------------------------------------
#ifndef FILEDATA_HPP_
#define FILEDATA_HPP_

//------------------------------------------------------------------------------
#include <string>

//------------------------------------------------------------------------------
class World;

//------------------------------------------------------------------------------
void saveWorld( const World & world, const std::string & path );

//------------------------------------------------------------------------------
#endif//FILEDATA_HPP_

//------------------------------------------------------------------------------
