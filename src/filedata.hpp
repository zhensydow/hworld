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
#include <boost/filesystem.hpp>

//------------------------------------------------------------------------------
class World;
class Entity;
//------------------------------------------------------------------------------
void saveWorld( const World & world, const boost::filesystem::path & folder );
std::shared_ptr<Entity> makeEntity( const std::string  & filename );

//------------------------------------------------------------------------------
#endif//FILEDATA_HPP_

//------------------------------------------------------------------------------
