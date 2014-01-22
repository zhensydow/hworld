//------------------------------------------------------------------------------
/** List of functions of game lua library.
*/
static const luaL_Reg gamelib[] = {
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
