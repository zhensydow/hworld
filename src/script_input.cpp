/**
    Copyright 2014, HexWorld Authors.

    This file is part of HexWorld.

    HexWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HexWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HexWorld.  If not, see <http://www.gnu.org/licenses/>.
**/
/** @file script_input.cpp
    @brief Input script library.
    @author Luis Cabellos
    @date 2014-01-23
*/
//------------------------------------------------------------------------------
#include "script.hpp"
#include <SFML/Graphics.hpp>
#include "engine.hpp"

//------------------------------------------------------------------------------
using namespace std;
using namespace sf;

//------------------------------------------------------------------------------
static int input_isKeyPressed( lua_State *lua ){
    auto val = luaL_checkint( lua, 1 );
    auto ret = Keyboard::isKeyPressed(static_cast<Keyboard::Key>(val));
    lua_pushboolean( lua, ret );
    return 1;
}

//------------------------------------------------------------------------------
static int input_isKeyDown( lua_State *lua ){
    auto val = luaL_checkint( lua, 1 );
    auto & engine = Engine::instance();
    auto & input = engine.getInput();
    auto ret = input.isKeyDown(val);
    lua_pushboolean( lua, ret );
    return 1;
}

//------------------------------------------------------------------------------
static int input_isKeyUp( lua_State *lua ){
    auto val = luaL_checkint( lua, 1 );
    auto & engine = Engine::instance();
    auto & input = engine.getInput();
    auto ret = input.isKeyUp(val);
    lua_pushboolean( lua, ret );
    return 1;
}

//------------------------------------------------------------------------------
static int input_isButtonPressed( lua_State *lua ){
    auto val = luaL_checkint( lua, 1 );
    auto ret = Mouse::isButtonPressed(static_cast<Mouse::Button>(val));
    lua_pushboolean( lua, ret );
    return 1;
}

//------------------------------------------------------------------------------
inline
void addKey( lua_State * lua, const char * name, Keyboard::Key k ){
    lua_pushstring( lua, name );                    // 2
    lua_pushnumber( lua, static_cast<int>(k) );     // 3
    lua_settable( lua, -3 );                        // 1
}

//------------------------------------------------------------------------------
inline
void addButton( lua_State * lua, const char * name, Mouse::Button b ){
    lua_pushstring( lua, name );                    // 2
    lua_pushnumber( lua, static_cast<int>(b) );     // 3
    lua_settable( lua, -3 );                        // 1
}

//------------------------------------------------------------------------------
static vector< pair<string, Keyboard::Key> > s_keys = {
    { "A", Keyboard::A },
    { "A", Keyboard::A },
    { "B", Keyboard::B },
    { "C", Keyboard::C },
    { "D", Keyboard::D },
    { "E", Keyboard::E },
    { "F", Keyboard::F },
    { "G", Keyboard::G },
    { "H", Keyboard::H },
    { "I", Keyboard::I },
    { "J", Keyboard::J },
    { "K", Keyboard::K },
    { "L", Keyboard::L },
    { "M", Keyboard::M },
    { "N", Keyboard::N },
    { "O", Keyboard::O },
    { "P", Keyboard::P },
    { "Q", Keyboard::Q },
    { "R", Keyboard::R },
    { "S", Keyboard::S },
    { "T", Keyboard::T },
    { "U", Keyboard::U },
    { "V", Keyboard::V },
    { "W", Keyboard::W },
    { "X", Keyboard::X },
    { "Y", Keyboard::Y },
    { "Z", Keyboard::Z },
    { "Num0", Keyboard::Num0 },
    { "Num1", Keyboard::Num1 },
    { "Num2", Keyboard::Num2 },
    { "Num3", Keyboard::Num3 },
    { "Num4", Keyboard::Num4 },
    { "Num5", Keyboard::Num5 },
    { "Num6", Keyboard::Num6 },
    { "Num7", Keyboard::Num7 },
    { "Num8", Keyboard::Num8 },
    { "Num9", Keyboard::Num9 },
    { "Escape", Keyboard::Escape },
    { "LControl", Keyboard::LControl },
    { "LShift", Keyboard::LShift },
    { "LAlt", Keyboard::LAlt },
    { "LSystem", Keyboard::LSystem },
    { "RControl", Keyboard::RControl },
    { "RShift", Keyboard::RShift },
    { "RAlt", Keyboard::RAlt },
    { "RSystem", Keyboard::RSystem },
    { "Menu", Keyboard::Menu },
    { "LBracket", Keyboard::LBracket },
    { "RBracket", Keyboard::RBracket },
    { "SemiColon", Keyboard::SemiColon },
    { "Comma", Keyboard::Comma },
    { "Period", Keyboard::Period },
    { "Quote", Keyboard::Quote },
    { "Slash", Keyboard::Slash },
    { "BackSlash", Keyboard::BackSlash },
    { "Tilde", Keyboard::Tilde },
    { "Equal", Keyboard::Equal },
    { "Dash", Keyboard::Dash },
    { "Space", Keyboard::Space },
    { "Return", Keyboard::Return },
    { "BackSpace", Keyboard::BackSpace },
    { "Tab", Keyboard::Tab },
    { "PageUp", Keyboard::PageUp },
    { "PageDown", Keyboard::PageDown },
    { "End", Keyboard::End },
    { "Home", Keyboard::Home },
    { "Insert", Keyboard::Insert },
    { "Delete", Keyboard::Delete },
    { "Add", Keyboard::Add },
    { "Subtract", Keyboard::Subtract },
    { "Multiply", Keyboard::Multiply },
    { "Divide", Keyboard::Divide },
    { "Left", Keyboard::Left },
    { "Right", Keyboard::Right },
    { "Up", Keyboard::Up },
    { "Down", Keyboard::Down },
    { "Numpad0", Keyboard::Numpad0 },
    { "Numpad1", Keyboard::Numpad1 },
    { "Numpad2", Keyboard::Numpad2 },
    { "Numpad3", Keyboard::Numpad3 },
    { "Numpad4", Keyboard::Numpad4 },
    { "Numpad5", Keyboard::Numpad5 },
    { "Numpad6", Keyboard::Numpad6 },
    { "Numpad7", Keyboard::Numpad7 },
    { "Numpad8", Keyboard::Numpad8 },
    { "Numpad9", Keyboard::Numpad9 },
    { "F1", Keyboard::F1 },
    { "F2", Keyboard::F2 },
    { "F3", Keyboard::F3 },
    { "F4", Keyboard::F4 },
    { "F5", Keyboard::F5 },
    { "F6", Keyboard::F6 },
    { "F7", Keyboard::F7 },
    { "F8", Keyboard::F8 },
    { "F9", Keyboard::F9 },
    { "F10", Keyboard::F10 },
    { "F11", Keyboard::F11 },
    { "F12", Keyboard::F12 },
    { "F13", Keyboard::F13 },
    { "F14", Keyboard::F14 },
    { "F15", Keyboard::F15 },
    { "Pause", Keyboard::Pause },
};

static vector< pair<string, Mouse::Button> > s_buttons = {
    { "MouseLeft", Mouse::Left },
    { "MouseRight", Mouse::Right },
    { "MouseMiddle", Mouse::Middle },
    { "MouseXButton1", Mouse::XButton1 },
    { "MouseXButton2", Mouse::XButton2 },
};

//--------------------------------------------------------------------------
/** List of functions of input lua library.
*/
static const luaL_Reg inputlib[] = {
    {"isKeyPressed",  input_isKeyPressed},
    {"isKeyDown",  input_isKeyDown},
    {"isKeyUp",  input_isKeyUp},
    {"isButtonPressed",  input_isButtonPressed},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openInput( lua_State * lua ){
    // set input functions
    luaL_register( lua, "input", inputlib );

    for( auto & k: s_keys ){
        addKey( lua, get<0>(k).data(), get<1>(k) );
    }

    for( auto & b: s_buttons ){
        addButton( lua, get<0>(b).data(), get<1>(b) );
    }

    // removes table
    lua_pop( lua, 1 );  // 0

}

//------------------------------------------------------------------------------
