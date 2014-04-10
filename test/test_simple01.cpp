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
/** @file test_simple01.cpp
    @brief Simple test
    @author Luis Cabellos
    @date 2014-04-08
*/
//------------------------------------------------------------------------------
#include <iostream>
#include "rangelist.hpp"

//------------------------------------------------------------------------------
int main(){
    //RangeList<float> rangef;
    std::cout <<  "Signed " << std::endl;
    RangeList<int> range;

    for( auto v: {1,2,4,7,8,9} ){
        range.insert( v );
    }

    for( int i = 0 ; i < 10 ; ++i ){
        std::cout << " test " << i << " " << range.contains(i) << std::endl;
    }

    for( auto it = range.beginItem() ; it != range.endItem() ; ++it ){
        std::cout << " it " << it->first << "-" << it->second << std::endl;
    }

    for( auto v: range ){
        std::cout << " val " << v << std::endl;
    }

    std::cout <<  "Unsigned " << std::endl;
    RangeList<unsigned int> rangeu;

    for( auto v: {4,7,1,2,0,-1,-2,6} ){
        rangeu.insert( v );
    }

    for( int i = 0 ; i < 10 ; ++i ){
        std::cout << " test " << i << " " << rangeu.contains(i) << std::endl;
    }

    for( auto it = rangeu.beginItem() ; it != rangeu.endItem() ; ++it ){
        std::cout << " it " << it->first << "-" << it->second << std::endl;
    }

    for( auto v: rangeu ){
        std::cout << " val " << v << std::endl;
    }

    std::cout <<  " Stripped " << std::endl;
    RangeList<int> rangei;

    for( int i = 1 ; i < 15 ; i+=2 ){
        rangei.insert( i );
    }

    for( int i = 0 ; i < 15 ; i+=2 ){
        rangei.insert( i );
    }

    for( auto it = rangei.beginItem() ; it != rangei.endItem() ; ++it ){
        std::cout << " it " << it->first << "-" << it->second << std::endl;
    }

    std::cout <<  " Remove " << std::endl;

    for( auto v: {1,7,4} ){
        range.remove( v );
    }

    for( auto it = range.beginItem() ; it != range.endItem() ; ++it ){
        std::cout << " it " << it->first << "-" << it->second << std::endl;
    }

    return 0;
}

//------------------------------------------------------------------------------
