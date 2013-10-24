//------------------------------------------------------------------------------
#include "script.hpp"
#include <SFML/Graphics.hpp>

//------------------------------------------------------------------------------
int isKeyPressed( lua_State *lua ){
    auto val = luaL_checkint( lua, 1 );
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(val));
}

//------------------------------------------------------------------------------
inline
void addKey( lua_State * lua, const char * name, sf::Keyboard::Key k ){
    lua_pushstring( lua, name );                    // 2
    lua_pushnumber( lua, static_cast<int>(k) );     // 3
    lua_settable( lua, -3 );                        // 1
}

//------------------------------------------------------------------------------
int isButtonPressed( lua_State *lua ){
    auto val = luaL_checkint( lua, 1 );
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(val));
}

//------------------------------------------------------------------------------
inline
void addButton( lua_State * lua, const char * name, sf::Mouse::Button b ){
    lua_pushstring( lua, name );                    // 2
    lua_pushnumber( lua, static_cast<int>(b) );     // 3
    lua_settable( lua, -3 );                        // 1
}

//------------------------------------------------------------------------------
void openInput( lua_State * lua ){
    using namespace sf;

    // set input
    lua_newtable( lua );                            // 1
    lua_pushstring( lua, "isKeyPressed");           // 2
    lua_pushcfunction( lua, isKeyPressed );         // 3
    lua_settable( lua, -3 );                        // 1

    auto keys = {
        std::make_pair( "A", Keyboard::A ),
        std::make_pair( "A", Keyboard::A ),
        std::make_pair( "B", Keyboard::B ),
        std::make_pair( "C", Keyboard::C ),
        std::make_pair( "D", Keyboard::D ),
        std::make_pair( "E", Keyboard::E ),
        std::make_pair( "F", Keyboard::F ),
        std::make_pair( "G", Keyboard::G ),
        std::make_pair( "H", Keyboard::H ),
        std::make_pair( "I", Keyboard::I ),
        std::make_pair( "J", Keyboard::J ),
        std::make_pair( "K", Keyboard::K ),
        std::make_pair( "L", Keyboard::L ),
        std::make_pair( "M", Keyboard::M ),
        std::make_pair( "N", Keyboard::N ),
        std::make_pair( "O", Keyboard::O ),
        std::make_pair( "P", Keyboard::P ),
        std::make_pair( "Q", Keyboard::Q ),
        std::make_pair( "R", Keyboard::R ),
        std::make_pair( "S", Keyboard::S ),
        std::make_pair( "T", Keyboard::T ),
        std::make_pair( "U", Keyboard::U ),
        std::make_pair( "V", Keyboard::V ),
        std::make_pair( "W", Keyboard::W ),
        std::make_pair( "X", Keyboard::X ),
        std::make_pair( "Y", Keyboard::Y ),
        std::make_pair( "Z", Keyboard::Z ),
        std::make_pair( "Num0", Keyboard::Num0 ),
        std::make_pair( "Num1", Keyboard::Num1 ),
        std::make_pair( "Num2", Keyboard::Num2 ),
        std::make_pair( "Num3", Keyboard::Num3 ),
        std::make_pair( "Num4", Keyboard::Num4 ),
        std::make_pair( "Num5", Keyboard::Num5 ),
        std::make_pair( "Num6", Keyboard::Num6 ),
        std::make_pair( "Num7", Keyboard::Num7 ),
        std::make_pair( "Num8", Keyboard::Num8 ),
        std::make_pair( "Num9", Keyboard::Num9 ),
        std::make_pair( "Escape", Keyboard::Escape ),
        std::make_pair( "LControl", Keyboard::LControl ),
        std::make_pair( "LShift", Keyboard::LShift ),
        std::make_pair( "LAlt", Keyboard::LAlt ),
        std::make_pair( "LSystem", Keyboard::LSystem ),
        std::make_pair( "RControl", Keyboard::RControl ),
        std::make_pair( "RShift", Keyboard::RShift ),
        std::make_pair( "RAlt", Keyboard::RAlt ),
        std::make_pair( "RSystem", Keyboard::RSystem ),
        std::make_pair( "Menu", Keyboard::Menu ),
        std::make_pair( "LBracket", Keyboard::LBracket ),
        std::make_pair( "RBracket", Keyboard::RBracket ),
        std::make_pair( "SemiColon", Keyboard::SemiColon ),
        std::make_pair( "Comma", Keyboard::Comma ),
        std::make_pair( "Period", Keyboard::Period ),
        std::make_pair( "Quote", Keyboard::Quote ),
        std::make_pair( "Slash", Keyboard::Slash ),
        std::make_pair( "BackSlash", Keyboard::BackSlash ),
        std::make_pair( "Tilde", Keyboard::Tilde ),
        std::make_pair( "Equal", Keyboard::Equal ),
        std::make_pair( "Dash", Keyboard::Dash ),
        std::make_pair( "Space", Keyboard::Space ),
        std::make_pair( "Return", Keyboard::Return ),
        std::make_pair( "BackSpace", Keyboard::BackSpace ),
        std::make_pair( "Tab", Keyboard::Tab ),
        std::make_pair( "PageUp", Keyboard::PageUp ),
        std::make_pair( "PageDown", Keyboard::PageDown ),
        std::make_pair( "End", Keyboard::End ),
        std::make_pair( "Home", Keyboard::Home ),
        std::make_pair( "Insert", Keyboard::Insert ),
        std::make_pair( "Delete", Keyboard::Delete ),
        std::make_pair( "Add", Keyboard::Add ),
        std::make_pair( "Subtract", Keyboard::Subtract ),
        std::make_pair( "Multiply", Keyboard::Multiply ),
        std::make_pair( "Divide", Keyboard::Divide ),
        std::make_pair( "Left", Keyboard::Left ),
        std::make_pair( "Right", Keyboard::Right ),
        std::make_pair( "Up", Keyboard::Up ),
        std::make_pair( "Down", Keyboard::Down ),
        std::make_pair( "Numpad0", Keyboard::Numpad0 ),
        std::make_pair( "Numpad1", Keyboard::Numpad1 ),
        std::make_pair( "Numpad2", Keyboard::Numpad2 ),
        std::make_pair( "Numpad3", Keyboard::Numpad3 ),
        std::make_pair( "Numpad4", Keyboard::Numpad4 ),
        std::make_pair( "Numpad5", Keyboard::Numpad5 ),
        std::make_pair( "Numpad6", Keyboard::Numpad6 ),
        std::make_pair( "Numpad7", Keyboard::Numpad7 ),
        std::make_pair( "Numpad8", Keyboard::Numpad8 ),
        std::make_pair( "Numpad9", Keyboard::Numpad9 ),
        std::make_pair( "F1", Keyboard::F1 ),
        std::make_pair( "F2", Keyboard::F2 ),
        std::make_pair( "F3", Keyboard::F3 ),
        std::make_pair( "F4", Keyboard::F4 ),
        std::make_pair( "F5", Keyboard::F5 ),
        std::make_pair( "F6", Keyboard::F6 ),
        std::make_pair( "F7", Keyboard::F7 ),
        std::make_pair( "F8", Keyboard::F8 ),
        std::make_pair( "F9", Keyboard::F9 ),
        std::make_pair( "F10", Keyboard::F10 ),
        std::make_pair( "F11", Keyboard::F11 ),
        std::make_pair( "F12", Keyboard::F12 ),
        std::make_pair( "F13", Keyboard::F13 ),
        std::make_pair( "F14", Keyboard::F14 ),
        std::make_pair( "F15", Keyboard::F15 ),
        std::make_pair( "Pause", Keyboard::Pause ),
    };

    for( auto & k: keys ){
        addKey( lua, std::get<0>(k), std::get<1>(k) );
    }

    lua_pushstring( lua, "isButtonPressed");        // 2
    lua_pushcfunction( lua, isButtonPressed );         // 3
    lua_settable( lua, -3 );                        // 1

    auto buttons = {
        std::make_pair( "MouseLeft", Mouse::Left ),
        std::make_pair( "MouseRight", Mouse::Right ),
        std::make_pair( "MouseMiddle", Mouse::Middle ),
        std::make_pair( "MouseXButton1", Mouse::XButton1 ),
        std::make_pair( "MouseXButton2", Mouse::XButton2 ),
    };

    for( auto & b: buttons ){
        addButton( lua, std::get<0>(b), std::get<1>(b) );
    }

    lua_setglobal( lua, "input" );                  // 0
}

//------------------------------------------------------------------------------
