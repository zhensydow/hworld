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
    GameState() noexcept;
    GameState( lua_State * lua ) noexcept;
    GameState( const GameState& ) = delete;
    GameState( GameState&& ) noexcept;
    GameState& operator=( const GameState& ) = delete;
    GameState& operator=( GameState&& ) noexcept;
    ~GameState() noexcept;

    void start();
    void update( double dt );
    void stop();

    lua_State * getLua() const;

private:
    lua_State * m_ls = nullptr;
};

//------------------------------------------------------------------------------
inline
lua_State * GameState::getLua() const{
    return m_ls;
}

//------------------------------------------------------------------------------
#endif//GAMESTATE_HPP_

//------------------------------------------------------------------------------
