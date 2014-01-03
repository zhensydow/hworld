/** @file resourcefactory.hpp
    @brief ResourceFactory declarations.
    @author Luis Cabellos
    @date 2014-01-03
*/
//------------------------------------------------------------------------------
#ifndef RESOURCEFACTORY_HPP_
#define RESOURCEFACTORY_HPP_

//------------------------------------------------------------------------------
#include <string>
#include <memory>
#include <unordered_map>

//------------------------------------------------------------------------------
class StaticModel;

//------------------------------------------------------------------------------
class ResourceFactory {
public:
    std::shared_ptr<StaticModel> getSimpleModel( const std::string & name );

private:
    std::unordered_map< std::string, std::shared_ptr<StaticModel> > m_modelMap;

};

//------------------------------------------------------------------------------
#endif//RESOURCEFACTORY_HPP_

//------------------------------------------------------------------------------
