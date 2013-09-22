/** @file terrainprop.cpp
    @brief TerrainProp definition.
    @author Luis Cabellos
    @date 2013-09-01
*/
//------------------------------------------------------------------------------
#include "terrainprop.hpp"
#include <queue>
#include "chunkprop.hpp"
#include "world.hpp"
#include "util.hpp"
#include "renderer.hpp"

//------------------------------------------------------------------------------
TerrainProp::TerrainProp( World & world ) : m_world(world) {
    ChunkProp::setupCommon();
}

//------------------------------------------------------------------------------
void TerrainProp::setFocus( unsigned int center ){
    auto queue = std::queue< std::pair< unsigned int, glm::vec3 > >();

    queue.emplace( std::make_pair( center, glm::vec3{0.0f, 0.0f, 0.0f} ) );

    m_chunks.clear();

    unsigned int idx;
    glm::vec3 pos;
    while( not queue.empty() and m_chunks.size() < 10 ){
        std::tie( idx, pos ) = queue.front();
        std::cout << "Inserted element: " << idx << " at ("
                  << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
        queue.pop();

        auto cit = m_chunks.find( idx );
        if( cit != m_chunks.end() ){
            std::cout << "Already inserted" << std::endl;
        }else{
            std::cout << "Not Already inserted" << std::endl;
            auto chunk = m_world.getChunk( idx );
            auto cprop = std::make_shared<ChunkProp>( createChunkProp( chunk ) );

            cprop->setPosition( pos );

            m_chunks.emplace( std::make_pair( idx, cprop ) );
        }
    }
}

//------------------------------------------------------------------------------
void TerrainProp::draw( Renderer & renderer ){
    for( auto chunk: m_chunks ){
        renderer.render( *chunk.second );
    }
}

//------------------------------------------------------------------------------
