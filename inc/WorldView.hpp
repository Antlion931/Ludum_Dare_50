#pragma once
#include "Node.hpp"
#include "Chunk.hpp"
#include "Y-sort.hpp"
#include "Player.hpp"

class WorldView : public Node
{
private:
    std::shared_ptr<sf::Texture> tileSet;

    std::vector<Chunk> loadedChunks;
    YSort entities;
    std::shared_ptr<Player> player;
    sf::Vector2i currentChunkCoords;
    
    void chunkChange(sf::Vector2i chunkCoords);

    Chunk allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo);
    void deallocateChunk(sf::Vector2i chunkCoords);

    bool isChunkAllocated(sf::Vector2i chunkCoords);
public:
    WorldView(std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet);

protected:
    void onDraw(sf::RenderTarget &target) override;
    void onUpdate(const sf::Time& delta) override;
};