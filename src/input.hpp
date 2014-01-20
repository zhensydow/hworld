/** @file input.hpp
    @brief Input class.
    @author Luis Cabellos
    @date 2014-01-20
*/
//------------------------------------------------------------------------------
#ifndef INPUT_HPP_
#define INPUT_HPP_

//------------------------------------------------------------------------------
class Input {
public:
    void beginFrame();

    void setKeyPressed( int key );
    void setKeyReleased( int key );

    bool isKeyDown( int key );
    bool isKeyUp( int key );

private:
    std::unordered_map< int, bool > m_down_map;
    std::unordered_map< int, bool > m_up_map;
};

//------------------------------------------------------------------------------
inline
void Input::beginFrame(){
    m_down_map.clear();
    m_up_map.clear();
}

//------------------------------------------------------------------------------
inline
void Input::setKeyPressed( int key ){
    m_down_map[key] = true;
}

//------------------------------------------------------------------------------
inline
void Input::setKeyReleased( int key ){
    m_up_map[key] = true;
}

//------------------------------------------------------------------------------
inline
bool Input::isKeyDown( int key ){
    return m_down_map[key];
}

//------------------------------------------------------------------------------
inline
bool Input::isKeyUp( int key ){
    return m_up_map[key];
}

//------------------------------------------------------------------------------
#endif//INPUT_HPP_

//------------------------------------------------------------------------------
