/*------------------------------------------------------------------------------
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
------------------------------------------------------------------------------*/
/** @file rangelist.cpp
    @brief RangeList class tests.
    @author Luis Cabellos
    @date 2014-04-11
*/
//------------------------------------------------------------------------------
#include <iostream>
#include "rangelist.hpp"

//------------------------------------------------------------------------------
bool testInsert(){
    constexpr int max = 10;
    RangeList<int> range;

    for( auto i = 0 ; i < max ; ++i ){
        range.insert( i );
    }

    for( auto i = 0 ; i < max ; ++i ){
        if( not range.contains( i ) ){
            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
bool testRemove(){
    constexpr int max = 10;
    RangeList<int> range;

    for( auto i = 0 ; i < max ; ++i ){
        range.insert( i );
    }

    for( auto i = 0 ; i < max ; ++i ){
        range.remove( i );
    }

    for( auto i = 0 ; i < max ; ++i ){
        if( range.contains( i ) ){
            return false;
        }
    }

    return true;
}

//------------------------------------------------------------------------------
bool testMerging(){
    constexpr int max = 15;
    RangeList<int> range;

    for( int i = 1 ; i < max ; i+=2 ){
        range.insert( i );
    }

    for( int i = 0 ; i < max ; i+=2 ){
        range.insert( i );
    }

    return std::distance( range.beginItem(), range.endItem() ) == 1;
}

//------------------------------------------------------------------------------
int main(){
    if( not testInsert() ){
        std::cout << "failure test Insert " << std::endl;
        return EXIT_FAILURE;
    }

    if( not testRemove() ){
        std::cout << "failure test Remove " << std::endl;
        return EXIT_FAILURE;
    }

    if( not testMerging() ){
        std::cout << "failure test Merging " << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
