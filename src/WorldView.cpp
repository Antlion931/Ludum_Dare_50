#include "WorldView.hpp"
#include <cmath>

WorldView::WorldView(std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet)
: player(_player), currentChunkCoords({0,0}), tileSet(_tileSet)
{
    loadedChunks.push_back(Chunk(_tileSet));
    loadedChunks[0] = (allocateChunk({-1,-1}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({ 0,-1}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({ 1,-1}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({-1, 0}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({ 0, 0}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({ 1, 0}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({-1, 1}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({ 0, 1}, currentChunkCoords));
    loadedChunks.push_back(allocateChunk({ 1, 1}, currentChunkCoords));
}

void WorldView::onDraw(sf::RenderTarget &target)
{
    // first we draw the chunks
    for(auto &chunk : loadedChunks)
    {
        chunk.draw(target);
    }

    entities.draw(target);
}

void WorldView::chunkChange(sf::Vector2i newChunkCoords)
{
    std::vector<Chunk> loadedChunksTemp = loadedChunks;
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(isChunkAllocated({newChunkCoords.x + j,newChunkCoords.y + i}))
            {
                std::cout << "@";
            }
            else
            {
                std::cout << "x";
            }
        }
        std::cout << "\n";
    }
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(isChunkAllocated({newChunkCoords.x + j, newChunkCoords.y + i}))
            {
                
                // to do ( nie alokowanie chunkow ktore juz mamy )
                //int relativex = currentChunkCoords.x - newChunkCoords.x;
                //int relativey = currentChunkCoords.y - newChunkCoords.y;
                //std::cout << "(" << j + 1 + (i + 1 ) * 3 << ", " << j + 1 - relativex + (i + 1 - relativey ) * 3 << ")";
                
                //loadedChunksTemp[ j + 1 + (i + 1 ) * 3] = loadedChunks[j + 1 - relativex + (i + 1 - relativey ) * 3];
                loadedChunksTemp[ j + 1 + (i + 1) * 3] = allocateChunk({j,i}, newChunkCoords);
            }
            else
            {
                std::cout << "(new)";
                loadedChunksTemp[ j + 1 + (i + 1) * 3] = allocateChunk({j,i}, newChunkCoords);
            }
            
        }
        std::cout << "\n";
    }
    loadedChunks = loadedChunksTemp;
    currentChunkCoords = newChunkCoords;
}


void WorldView::onUpdate(const sf::Time& delta)
{

    sf::Vector2f playerCoords = player->getGlobalTransform().getPosition();
    sf::Vector2i WorldChunkSize = loadedChunks[0].getWorldChunkSize();

    // find which chunk the player is currently in
    sf::Vector2i newChunkCoords;
    newChunkCoords.x = floor(playerCoords.x / WorldChunkSize.x);
    newChunkCoords.y = floor(playerCoords.y / WorldChunkSize.y);

    //currentChunkCoords = newChunkCoords;
    //std::cout << "player coords: " << playerCoords.x << ", " << playerCoords.y << std::endl;
    //std::cout << "player chunk coords: " << currentChunkCoords.x << ", " << currentChunkCoords.y << std::endl;

    if( currentChunkCoords != newChunkCoords )
        chunkChange(newChunkCoords);
}


Chunk WorldView::allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo)
{
    Chunk newChunk(tileSet);

    // get relative coords of the chunk
    sf::Vector2i WorldChunkSize = newChunk.getWorldChunkSize();
    int relativex = relativeTo.x - chunkCoords.x;
    int relativey = relativeTo.y - chunkCoords.y;
    newChunk.translate({relativex * WorldChunkSize.x, relativey * WorldChunkSize.y});

    return newChunk;
}
void WorldView::deallocateChunk(sf::Vector2i chunkCoords)
{

}


bool WorldView::isChunkAllocated(sf::Vector2i chunkCoords)
{
    int xdiff = currentChunkCoords.x - chunkCoords.x;
    int ydiff = currentChunkCoords.y - chunkCoords.y;
    /*return abs(xdiff) + abs(ydiff) <= 1
    || (abs(xdiff) == 1 && abs(ydiff == 1));*/
    return -1 <= xdiff && xdiff <= 1 && -1 <= ydiff && ydiff <= 1;
    //return 1;
}