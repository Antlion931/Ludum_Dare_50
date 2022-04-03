#include "WorldView.hpp"
#include <cmath>
#include <memory>

WorldView::WorldView(std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet)
: player(_player), currentCenterCoords({0,0}), tileSet(_tileSet)
{
    allocateChunk({-1,-1}, currentCenterCoords);
    allocateChunk({ 0,-1}, currentCenterCoords);
    allocateChunk({ 1,-1}, currentCenterCoords);
    allocateChunk({-1, 0}, currentCenterCoords);
    allocateChunk({ 0, 0}, currentCenterCoords);
    allocateChunk({ 1, 0}, currentCenterCoords);
    allocateChunk({-1, 1}, currentCenterCoords);
    allocateChunk({ 0, 1}, currentCenterCoords);
    allocateChunk({ 1, 1}, currentCenterCoords);

    //int chunkx = chunkMap[{0,0}]->getGlobalTransform().getPosition().x;
    //int chunky = chunkMap[{0,0}]->getGlobalTransform().getPosition().y;
    //std::cout << "Drawing a chunk at: (" << chunkx << ", " << chunky << ")\n" ;
}

void WorldView::onDraw(sf::RenderTarget &target)
{
    // first we draw the chunks
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            int chunkx = chunkMap[{i,j}]->getGlobalTransform().getPosition().x;
            int chunky = chunkMap[{i,j}]->getGlobalTransform().getPosition().y;
            //std::cout << "Drawing a chunk at: (" << chunkx << ", " << chunky << ")\n" ;
            //chunkMap[{i, j}]->translate({0.001f,0.001f});
            chunkMap[{i, j}]->draw(target);
        }
    }
    /*for(auto &chunk : loadedChunks)
    {
        int chunkx = chunk->getGlobalTransform().getPosition().x;
        int chunky = chunk->getGlobalTransform().getPosition().y;
        //std::cout << "Drawing a chunk at: (" << chunkx << ", " << chunky << ")\n" ;
        chunk->draw(target);
    }*/

    entities.draw(target);
}

void WorldView::chunkChange(sf::Vector2i newCenterCoords)
{
    // we need to load new chunks
}


void WorldView::onUpdate(const sf::Time& delta)
{
    sf::Vector2f playerCoords = player->getGlobalTransform().getPosition();
    sf::Vector2i WorldChunkSize = chunkMap[{0,0}]->getWorldChunkSize();

    // find which chunk the player is currently in
    sf::Vector2i newCenterCoords;
    newCenterCoords.x = floor(playerCoords.x / WorldChunkSize.x);
    newCenterCoords.y = floor(playerCoords.y / WorldChunkSize.y);

    //currentCenterCoords = newCenterCoords;
    //std::cout << "player coords: " << playerCoords.x << ", " << playerCoords.y << std::endl;
    //std::cout << "player chunk coords: " << currentCenterCoords.x << ", " << currentCenterCoords.y << std::endl;

    if( currentCenterCoords != newCenterCoords )
        chunkChange(newCenterCoords);
}


std::shared_ptr<Chunk> WorldView::allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo)
{
    sf::Vector2i relativeCoords = {relativeTo.x - chunkCoords.x, relativeTo.y - chunkCoords.y};
    if(chunkMap.count(relativeCoords))
    {
        std::cout << "Found the chunk at: " << relativeCoords.x << ", " << relativeCoords.y << ")\n";
        return chunkMap.at(relativeCoords);
    }
    std::shared_ptr<Chunk> newChunk = std::make_shared<Chunk>(Chunk(tileSet));

    // get relative coords of the chunk
    sf::Vector2i WorldChunkSize = newChunk->getWorldChunkSize();
    //std::cout << "Previous translation: (" << newChunk->getGlobalTransform().getPosition().x << ", " << newChunk->getGlobalTransform().getPosition().y << ")\n";
    newChunk->translate({relativeCoords.x * WorldChunkSize.x, relativeCoords.y * WorldChunkSize.y});
    std::cout << "Allocating a chunk at: (" << relativeCoords.x << ", " << relativeCoords.y << ")\n";
    std::cout << "Translation vector: (" << relativeCoords.x * WorldChunkSize.x << ", " << relativeCoords.y * WorldChunkSize.y << ")\n";

    chunkMap.insert({relativeCoords, newChunk});
    //addChild(newChunk);
    return newChunk;
}


void WorldView::deallocateChunk(sf::Vector2i chunkCoords)
{

}
