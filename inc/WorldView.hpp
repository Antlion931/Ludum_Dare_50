#pragma once
#include "Node.hpp"
#include "Chunk.hpp"
#include "Y-sort.hpp"
#include "Player.hpp"
#include <unordered_map>
#include <map>


class WorldView : public Node
{
private:
    struct KeyHasher
    {
        std::size_t operator()(const sf::Vector2i& k) const
        {
            return ((std::hash<int>()(k.x) ^ (std::hash<int>()(k.y) << 1)) >> 1);
        }
    };

    std::shared_ptr<sf::Texture> tileSet;
    
    std::unordered_map<sf::Vector2i, Chunk, KeyHasher> chunkMap;

    YSort entities;
    std::shared_ptr<Player> player;
    sf::Vector2i currentCenterCoords;
    
    void chunkChange(sf::Vector2i chunkCoords);

    void allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo);
    void deallocateChunk(sf::Vector2i chunkCoords);
    void deallocateChunks();

public:
    WorldView(std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet);

protected:
    void onDraw(sf::RenderTarget &target) override; 
    void onUpdate(const sf::Time& delta) override;
};