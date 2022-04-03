#include "WorldView.hpp"
#include <cmath>
#include <memory>

WorldView::WorldView(std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet)
: player(_player), currentCenterCoords({100,100}), tileSet(_tileSet)
{
    //allocateChunk({-1,-1}, currentCenterCoords);
    //allocateChunk({ 0,-1}, currentCenterCoords);
    //allocateChunk({ 1,-1}, currentCenterCoords);
    //allocateChunk({-1, 0}, currentCenterCoords);
    //allocateChunk({ 0, 0}, currentCenterCoords);
    //allocateChunk({ 1, 0}, currentCenterCoords);
    //allocateChunk({-1, 1}, currentCenterCoords);
    //allocateChunk({ 0, 1}, currentCenterCoords);
    //allocateChunk({ 1, 1}, currentCenterCoords);
}

void WorldView::onDraw(sf::RenderTarget &target)
{
    // first we draw the chunks
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            sf::Vector2i offsetChunk = {currentCenterCoords.x - i,currentCenterCoords.y - j};
            chunkMap[offsetChunk].draw(target);
        }
    }

    //entities.draw(target);
}

void WorldView::chunkChange(sf::Vector2i newCenterCoords)
{
    // we need to load new chunks
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            allocateChunk({j,i}, newCenterCoords);
        }
    }
    currentCenterCoords = newCenterCoords;
}


void WorldView::onUpdate(const sf::Time& delta)
{
    sf::Vector2f playerCoords = player->getGlobalTransform().getPosition();
    sf::Vector2i WorldChunkSize = Chunk(tileSet).getWorldChunkSize();

    // find which chunk the player is currently in
    sf::Vector2i newCenterCoords;
    newCenterCoords.x = floor(playerCoords.x / WorldChunkSize.x);
    newCenterCoords.y = floor(playerCoords.y / WorldChunkSize.y);

    if( currentCenterCoords != newCenterCoords )
        chunkChange(newCenterCoords);
}


void WorldView::allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo)
{
    sf::Vector2i relativeCoords = {relativeTo.x - chunkCoords.x, relativeTo.y - chunkCoords.y};
    if(chunkMap.count(relativeCoords))
    {
        std::cout << "Found the chunk at: " << relativeCoords.x << ", " << relativeCoords.y << ")\n";
        return;
    }
    Chunk newChunk = Chunk(tileSet);

    // get relative coords of the chunk
    sf::Vector2i WorldChunkSize = newChunk.getWorldChunkSize();
    newChunk.translate({relativeCoords.x * WorldChunkSize.x, relativeCoords.y * WorldChunkSize.y});

    std::shared_ptr<Chunk> newChunkPtr = std::make_shared<Chunk>(newChunk);

    chunkMap.insert({relativeCoords, newChunk});
    return;
}


void WorldView::deallocateChunk(sf::Vector2i chunkCoords)
{

}
