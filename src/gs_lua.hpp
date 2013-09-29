/** @file gs_lua.hpp
    @brief GameState in Lua declaration.
    @author Luis Cabellos
    @date 2013-09-29
*/
//------------------------------------------------------------------------------
#ifndef GS_LUA_HPP_
#define GS_LUA_HPP_

//------------------------------------------------------------------------------
#include <string>
#include "gamestate.hpp"

//------------------------------------------------------------------------------
struct lua_State;

//------------------------------------------------------------------------------
class GSLua final : public GameState {
public:
    GSLua( lua_State * lua );

    ~GSLua();

    void start() override;
    void update( double dt ) override;
    void stop() override;

private:
    lua_State * m_ls = nullptr;
};

//------------------------------------------------------------------------------
#endif//GS_LUA_HPP_

//------------------------------------------------------------------------------
