/** @file script_game.cpp
    @brief Game script library.
    @author Luis Cabellos
    @date 2014-01-22
*/
//------------------------------------------------------------------------------
#include "script.hpp"
#include "engine.hpp"

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
static int game_setSunDir( lua_State *ls ){
    auto x = luaL_checknumber( ls, 1 );
    auto y = luaL_checknumber( ls, 2 );
    auto z = luaL_checknumber( ls, 3 );
    auto & engine = Engine::instance();
    auto & renderer = engine.getRenderer();

    renderer.setSunDir( glm::vec3( x, y, z ) );

    return 0;
}

//------------------------------------------------------------------------------
/** List of functions of game lua library.
*/
static const luaL_Reg gamelib[] = {
    {"setSunDir", game_setSunDir},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openGame( lua_State * lua ){
    // set engine functions
    luaL_register( lua, "game", gamelib );
    // removes table
    lua_pop( lua, 1 );
}

//------------------------------------------------------------------------------
