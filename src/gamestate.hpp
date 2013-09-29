/** @file gamestate.hpp
    @brief GameState declaration.
    @author Luis Cabellos
    @date 2013-09-28
*/
//------------------------------------------------------------------------------
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

//------------------------------------------------------------------------------
class GameState {
public:
    GameState() = default;
    GameState( const GameState& ) = default;
    GameState( GameState&& ) = default;
    GameState& operator=( const GameState& ) = default;
    GameState& operator=( GameState&& ) = default;
    virtual ~GameState();

    virtual void update( double dt ) = 0;

private:
};

//------------------------------------------------------------------------------
inline
GameState::~GameState(){
    //empty
};

//------------------------------------------------------------------------------
#endif//GAMESTATE_HPP_

//------------------------------------------------------------------------------
