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
    RangeList<int> range;

    range.insert( 1 );
    range.insert( 2 );
    range.insert( 4 );
    range.insert( 7 );
    range.insert( 8 );
    range.insert( 6 );

    for( int i = 0 ; i < 10 ; ++i ){
        std::cout << " test " << i << " " << range.contains(i) << std::endl;
    }

    return 0;
}

//------------------------------------------------------------------------------
