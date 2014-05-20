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
#include <memory>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <SFML/Graphics.hpp>
#include "glminc.hpp"
#include "constants.hpp"
#include "chunk.hpp"
#include "worldarea.hpp"

//------------------------------------------------------------------------------
using namespace std;

//------------------------------------------------------------------------------
void drawDebugArea( sf::RenderTexture * texture, const WorldArea & area  );

//------------------------------------------------------------------------------
bool insideRect( const glm::vec2 & a, const glm::vec2 & b, const glm::vec2 & p )
{
    return p.x >= a.x and p.y >= a.y and p.x < b.x and p.y < b.y;
}

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
unordered_map< ChunkID, Chunk >::iterator
getChunkInArea( unordered_map< ChunkID, Chunk > & chunks,
                const WorldArea & area ){

    auto it = find_if( begin(chunks), end(chunks),
                       [&]( pair< const ChunkID, Chunk > & c ){
                           return area.inside( c.second.m_pos );
                       } );
    return it;
}

//------------------------------------------------------------------------------
unordered_map< ChunkID, Chunk >::iterator
findChunk( unordered_map< ChunkID, Chunk > & chunks,
           const glm::vec2 & pos ){
    return find_if( begin(chunks), end(chunks),
                    [&]( pair< const ChunkID, Chunk > & c ){
                        return equalCenter( c.second.m_pos, pos );
                    } );
}

//------------------------------------------------------------------------------
void genTileDivision( const vector<WorldArea> & areas,
                      const glm::vec2 & a, const glm::vec2 & b,
                      sf::RenderTexture * texture )
{
    assert( areas.size() > 0 && "no areas" );

    ChunkID nextID = 0;
    unordered_map< ChunkID, Chunk > chunks;

    // insert first candidate from the first area
    auto & firstArea = areas[0];

    Chunk root;
    root.m_pos = firstArea.getMinBound() +
        glm::vec2( TILE_RADIUS, TILE_RADIUS );
    chunks[ nextID++ ] = root;

    for( auto & area: areas ){
        auto current = getChunkInArea( chunks, area );
        while( current != end( chunks ) ){
            auto chunkid = current->first;
            auto chunk = current->second;
            chunks.erase( current );

            cout << "chunk inside area " << chunkid << endl;

            for( unsigned int i = 0 ; i < Chunk::NNEIGHBOURS ; ++i ){
                if( chunk.m_neighbours[ i ] == CHUNK_NULL_IDX ){
                    auto childPos = chunk.neighbourPosition( i );

                    if( insideRect( a, b, childPos ) ){
                        auto childlink = mirrorNeigh( i );

                        cout << "insert child chunk " <<
                            i << " -> " << childlink << " " <<
                            childPos.x << ", " << childPos.y << endl;

                        auto it = findChunk( chunks, childPos );
                        if( it != end(chunks) ){
                            cout << "already done" << endl;
                            it->second.m_neighbours[ childlink ] = chunkid;
                            chunk.m_neighbours[ i ] = it->first;
                        }else{
                            cout << "new position" << endl;
                            Chunk child;
                            child.m_pos = childPos;
                            auto childid = nextID++;

                            child.m_neighbours[ childlink ] = chunkid;

                            chunk.m_neighbours[ i ] = childid;

                            chunks[ childid ] = child;
                        }
                    }
                }
            }

            current = getChunkInArea( chunks, area );
        }

        drawDebugArea( texture, area );
    }

    cout << "Total TILES : " << nextID << endl;
    if( chunks.size() > 0 ){
        cout << "Warning: Tiles outside areas : " << chunks.size() << endl;
    }
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
    tiles.reserve( (int)estimated );

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

        if( insideRect( a, b, pos ) ){
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
                if( pid < tiles.size() ){
                    auto & pchunk = tiles[ pid ];
                    pchunk.m_neighbours[ plink ] = k;
                }
            }else{
                Chunk chunk;
                chunk.m_pos = pos;
                auto ownlink = mirrorNeigh( plink );
                chunk.m_neighbours[ ownlink ] = pid;

                tiles.push_back( chunk );

                auto ownid = tiles.size() - 1;
                if( pid < tiles.size() ){
                    auto & pchunk = tiles[ pid ];
                    pchunk.m_neighbours[ plink ] = ownid;
                }

                for( unsigned int i = 0 ; i < Chunk::NNEIGHBOURS ; ++i ){
                    if( chunk.m_neighbours[ i ] == CHUNK_NULL_IDX ){
                        auto newPos = chunk.neighbourPosition( i );
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
void drawDebugArea( sf::RenderTexture * texture,
                    const WorldArea & area  )
{
    if( not texture ){
        return;
    }

    auto qcolor = sf::Color( 255, 0, 0, 255 );
    sf::Vertex qlines[] = {
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor )
    };

    auto minb = area.getMinBound();
    auto maxb = area.getMaxBound();

    qlines[0].position = {minb.x, minb.y};
    qlines[1].position = {maxb.x, minb.y};
    qlines[2].position = {maxb.x, maxb.y};
    qlines[3].position = {minb.x, maxb.y};
    qlines[4].position = {minb.x, maxb.y};
    texture->draw( qlines, 5, sf::LinesStrip );
}

//------------------------------------------------------------------------------
void drawDebugBMP( sf::RenderTexture * texture,
                   const vector<WorldArea> & areas,
                   const vector<Chunk> & tiles )
{
    if( not texture ){
        return;
    }

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
        texture->draw( circle );
        line[0].position = { t.m_pos.x, t.m_pos.y };
        for( auto & nn: t.m_neighbours ){
            if( nn != CHUNK_NULL_IDX ){
                auto & pchunk = tiles[ nn ];
                line[1].position = { pchunk.m_pos.x, pchunk.m_pos.y };
                texture->draw( line, 2, sf::Lines );
            }
        }
    }

    auto qcolor = sf::Color( 255, 0, 0, 255 );
    sf::Vertex qlines[] = {
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor ),
        sf::Vertex( sf::Vector2f( 0, 0 ), qcolor )
    };

    for( auto & a: areas ){
        auto minb = a.getMinBound();
        auto maxb = a.getMaxBound();

        qlines[0].position = {minb.x, minb.y};
        qlines[1].position = {maxb.x, minb.y};
        qlines[2].position = {maxb.x, maxb.y};
        qlines[3].position = {minb.x, maxb.y};
        qlines[4].position = {minb.x, maxb.y};
        texture->draw( qlines, 5, sf::LinesStrip );
    }
}

//------------------------------------------------------------------------------
unique_ptr<sf::RenderTexture> makeDebugTexture( const glm::vec2 & a, const glm::vec2 & b ){
    auto renderTexture = unique_ptr<sf::RenderTexture>( new sf::RenderTexture );
    if( not renderTexture->create( 1000, 1000 ) ){
        cout << "ERROR: Can't create debug BMP" << endl;
        return nullptr;
    }

    auto view = sf::View( sf::FloatRect( a.x, a.y, (b.x - a.x), (b.y - a.y) ) );

    renderTexture->setView( view );
    renderTexture->clear();

    return renderTexture;
}

//------------------------------------------------------------------------------
void saveDebugTexture( sf::RenderTexture * texture, const string & name ){
    if( texture ){
        texture->display();
        auto image = texture->getTexture().copyToImage();
        image.saveToFile( name );
    }
}

//------------------------------------------------------------------------------
int main(){
    cout << "Generating Tile Map" << endl;

    auto bound0 = glm::vec2( 0.0f, 0.0f );
    auto bound1 = glm::vec2( 500.0f, 500.0f );

    cout << " * world areas ..." << endl;
    auto areas = genWorldAreas( bound0, bound1, 8, 8 );
    cout << " * chunk tiles ..." << endl;
    auto tiles = genTileDivision( bound0, bound1 );

    auto texture0 = makeDebugTexture( bound0, bound1 );

    genTileDivision( areas, bound0, bound1, texture0.get() );

    cout << endl << "Total Tiles : " << tiles.size() << endl;

    cout << "Saving Debug BMP" << endl;
    auto texture1 = makeDebugTexture( bound0, bound1 );
    drawDebugBMP( texture1.get(), areas, tiles );
    saveDebugTexture( texture0.get(), "gendebug0.png" );
    saveDebugTexture( texture1.get(), "gendebug1.png" );

    return 0;
}

//------------------------------------------------------------------------------
