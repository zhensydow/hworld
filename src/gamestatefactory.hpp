/** @file gamestatefactory.hpp
    @brief GameStateFactory declaration.
    @author Luis Cabellos
    @date 2013-09-29
*/
//------------------------------------------------------------------------------
#ifndef GAMESTATEFACTORY_HPP_
#define GAMESTATEFACTORY_HPP_

//------------------------------------------------------------------------------
#include <memory>
#include <boost/filesystem.hpp>

//------------------------------------------------------------------------------
class GameState;

//------------------------------------------------------------------------------
class GameStateFactory {
public:
    std::shared_ptr<GameState> makeGSLua( const std::string & name ) const;

private:
    boost::filesystem::path m_datadir = "data/state";
};

//------------------------------------------------------------------------------
#endif//GAMESTATEFACTORY_HPP_

//------------------------------------------------------------------------------
