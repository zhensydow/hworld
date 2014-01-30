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
/** @file debug.hpp
    @brief Debug functions.
    @author Luis Cabellos
    @date 2014-01-29
*/
//------------------------------------------------------------------------------
#ifndef DEBUG_HPP_
#define DEBUG_HPP_

//------------------------------------------------------------------------------
#include <iostream>

//------------------------------------------------------------------------------
enum class LogLevel{
    LL_ERROR = 0,
        LL_WARNING = 1,
        LL_INFO = 2,
        LL_DEBUG = 3
};

//------------------------------------------------------------------------------
void outMemoryInfo();

//------------------------------------------------------------------------------
void setLogLevel( LogLevel ll );
void printLogTag( LogLevel ll );
bool logEnabled( LogLevel ll );

//------------------------------------------------------------------------------
template<typename X>
void printLog( const X & x ){
    std::cout << x << std::endl;
}

template<typename X, typename... XS>
void printLog( const X & x, XS... xs ){
    std::cout << x; printLog( xs... );
}

//------------------------------------------------------------------------------
template<typename... XS>
void log( LogLevel ll, XS... xs ){
    if( logEnabled( ll ) ){
        printLogTag(ll); printLog( xs... );
    }
}

//------------------------------------------------------------------------------
template<typename... XS>
inline
void logE( XS... xs ){
    log( LogLevel::LL_ERROR, xs... );
}

//------------------------------------------------------------------------------
template<typename... XS>
inline
void logW( XS... xs ){
    log( LogLevel::LL_WARNING, xs... );
}

//------------------------------------------------------------------------------
template<typename... XS>
inline
void logI( XS... xs ){
    log( LogLevel::LL_INFO, xs... );
}

//------------------------------------------------------------------------------
template<typename... XS>
inline
void logD( XS... xs ){
    log( LogLevel::LL_DEBUG, xs... );
}

//------------------------------------------------------------------------------
#endif//DEBUG_HPP_

//------------------------------------------------------------------------------
