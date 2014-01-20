//------------------------------------------------------------------------------
#ifndef SCRIPT_HPP_
#define SCRIPT_HPP_

//------------------------------------------------------------------------------
#include "lua.hpp"

//------------------------------------------------------------------------------
class Entity;

//------------------------------------------------------------------------------
void openEngine( lua_State * lua );
void openInput( lua_State * lua );
void openTerminal( lua_State * lua );
void openGLM( lua_State * lua );
void lua_pushEntity( lua_State * lua, Entity & entity );
Entity * lua_checkEntity( lua_State * lua, int index );

//------------------------------------------------------------------------------
#endif//SCRIPT_HPP_

//------------------------------------------------------------------------------
