//------------------------------------------------------------------------------
#include "script.hpp"
#include <SFML/Graphics.hpp>

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
int input_isButtonPressed( lua_State *lua ){
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
    {"isButtonPressed",  input_isButtonPressed},
    {nullptr, nullptr}
};

//------------------------------------------------------------------------------
void openInput( lua_State * lua ){
    // set engine functions
    luaL_register( lua, "input", inputlib );
    // set input
    // lua_newtable( lua );                            // 1
    // lua_pushstring( lua, "isKeyPressed");           // 2
    // lua_pushcfunction( lua, isKeyPressed );         // 3
    // lua_settable( lua, -3 );                        // 1
    // lua_pushstring( lua, "isButtonPressed");        // 2
    // lua_pushcfunction( lua, isButtonPressed );      // 3
    // lua_settable( lua, -3 );                        // 1
    // lua_setglobal( lua, "input" );                  // 0

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
