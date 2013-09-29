/** @file gamestate.hpp
    @brief GameState declaration.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

//------------------------------------------------------------------------------
struct lua_State;

//------------------------------------------------------------------------------
class GameState final {
public:
    GameState( lua_State * lua );
    GameState( const GameState& ) = default;
    GameState( GameState&& ) = default;
    GameState& operator=( const GameState& ) = default;
    GameState& operator=( GameState&& ) = default;
    ~GameState();

    void start();
    void update( double dt );
    void stop();

private:
    lua_State * m_ls = nullptr;
};

//------------------------------------------------------------------------------
#endif//GAMESTATE_HPP_

//------------------------------------------------------------------------------
