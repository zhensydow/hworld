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
/** @file main_genhworld.cpp
    @brief Main file fo genhworld tool
    @author Luis Cabellos
    @date 2014-04-03
*/
//------------------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
#include "glminc.hpp"
#include "constants.hpp"
#include "chunk.hpp"
#include "worldarea.hpp"

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
bool equalCenter( const glm::vec2 & a, const glm::vec2 & b ){
    if( abs( a.x - b.x ) >= 0.01f ){
        return false;
    }

    if( abs( a.y - b.y ) >= 0.01f ){
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
ChunkID mirrorNeigh( ChunkID orig ){
    return (orig + 3) % Chunk::NNEIGHBOURS;
}

//------------------------------------------------------------------------------
vector<WorldArea> genWorldAreas( const glm::vec2 & a, const glm::vec2 & b,
                                 unsigned int numw, unsigned int numh )
{
    vector<WorldArea> areas;

    areas.reserve( numw*numh );

    auto w = b.x - a.x;
    auto h = b.y - a.y;

    for( unsigned int j = 0 ; j < numh ; ++j ){
        auto h0 = a.y + j*(w/numw);
        auto h1 = a.y + (j+1)*(w/numw);
        for( unsigned int i = 0 ; i < numw ; ++i ){
            auto w0 = a.x + i*(h/numh);
            auto w1 = a.x + (i+1)*(h/numh);
            areas.emplace_back( glm::vec2(w0,h0), glm::vec2(w1,h1) );
        }
    }

    return areas;
}

//------------------------------------------------------------------------------
vector<Chunk> genTileDivision( const glm::vec2 & a, const glm::vec2 & b ){
    using ParentChunk = tuple< ChunkID, unsigned int >;

    vector<Chunk> tiles;

    auto w = b.x - a.x;
    auto h = b.y - a.y;
    float estimated = (w/(TILE_RADIUS*4)) * (h/(2.5*TILE_OFFSET_Y));
    float lastPercent = 0.0f;

    cout << estimated << endl;

    auto qwork = queue< pair< ParentChunk, glm::vec2 > >();

    qwork.emplace( make_pair( make_tuple( CHUNK_NULL_IDX, 0 ),
                              a + glm::vec2( TILE_RADIUS, TILE_RADIUS ) ) );

    ParentChunk parent;
    glm::vec2 pos;
    while( not qwork.empty() ){
        tie( parent, pos ) = qwork.front();
        auto pid = get<0>(parent);
        auto plink = get<1>(parent);
        qwork.pop();

        if( pos.x >= a.x and pos.y >= a.y and pos.x <= b.x and pos.y <= b.y ){
            unsigned int k = 0;
            for( k = 0 ; k < tiles.size() ; ++k ){
                if( equalCenter( tiles[k].m_pos, pos ) ){
                    break;
                }
            }

            if( k != tiles.size() ){
                auto & cchunk = tiles[ k ];
                auto clink = mirrorNeigh( plink );
                cchunk.m_neighbours[ clink ] = pid;
                auto & pchunk = tiles[ pid ];
                pchunk.m_neighbours[ plink ] = k;
            }else{
                Chunk chunk;
                chunk.m_pos = pos;
                auto ownlink = mirrorNeigh( plink );
                chunk.m_neighbours[ ownlink ] = pid;

                tiles.push_back( chunk );

                auto ownid = tiles.size() - 1;
                auto & pchunk = tiles[ pid ];
                pchunk.m_neighbours[ plink ] = ownid;

                for( unsigned int i = 0 ; i < Chunk::NNEIGHBOURS ; ++i ){
                    if( chunk.m_neighbours[ i ] == CHUNK_NULL_IDX ){
                        auto offset = glm::rotate( glm::vec2( CHUNK_OFFSET_X,
                                                              CHUNK_OFFSET_Y ),
                                                   sixthPart * i );

                        auto newPos = chunk.m_pos + offset;
                        qwork.emplace( make_pair( make_tuple( ownid, i ),
                                                  newPos ) );
                    }
                }

                auto currentPercent = 100.f * (float(ownid) / estimated);
                if( currentPercent > (lastPercent + 5.0f ) ){
                    cout << int(currentPercent) << " " << flush;
                    lastPercent = currentPercent;
                }
            }
        }
    }

    cout << endl;

    return tiles;
}

//------------------------------------------------------------------------------
void saveDebugBMP( const vector<Chunk> & tiles,
                   const glm::vec2 & a, const glm::vec2 & b )
{
    sf::RenderTexture renderTexture;
    if( not renderTexture.create( 1000, 1000 ) ){
        cout << "ERROR: Can't create debug BMP" << endl;
        return;
    }

    auto view = sf::View( sf::FloatRect( a.x, a.y, (b.x - a.x), (b.y - a.y) ) );

    renderTexture.setView( view );

    renderTexture.clear();

    sf::CircleShape circle( 1 );
    circle.setOrigin( 1, 1 );
    sf::Vertex line[] = {
        sf::Vertex( sf::Vector2f( 0, 0 ),
                    sf::Color( 200, 200, 200, 100 ) ),
        sf::Vertex( sf::Vector2f( 0, 0 ),
                    sf::Color( 200, 200, 200, 100 ) )
    };

    for( auto & t: tiles ){
        circle.setPosition( t.m_pos.x, t.m_pos.y );
        renderTexture.draw( circle );
        line[0].position = { t.m_pos.x, t.m_pos.y };
        for( auto & nn: t.m_neighbours ){
            if( nn != CHUNK_NULL_IDX ){
                auto & pchunk = tiles[ nn ];
                line[1].position = { pchunk.m_pos.x, pchunk.m_pos.y };
                renderTexture.draw( line, 2, sf::Lines );
            }
        }
    }


    renderTexture.display();

    auto image = renderTexture.getTexture().copyToImage();

    image.saveToFile( "text.png" );
}

//------------------------------------------------------------------------------
int main(){
    cout << "Generating Tile Map" << endl;

    auto bound0 = glm::vec2( 0.0f, 0.0f );
    auto bound1 = glm::vec2( 500.0f, 500.0f );

    cout << " * world areas ..." << endl;
    auto areas = genWorldAreas( bound0, bound1, 10, 10 );
    cout << " * chunk tiles ..." << endl;
    auto tiles = genTileDivision( bound0, bound1 );

    cout << endl << "Total Tiles : " << tiles.size() << endl;

    cout << "Saving Debug BMP" << endl;
    saveDebugBMP( tiles, bound0, bound1 );

    return 0;
}

//------------------------------------------------------------------------------
