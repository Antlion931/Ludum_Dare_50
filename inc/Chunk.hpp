#pragma once
#include "Node.hpp"
#include "TileMap.hpp"
#include "NPC.hpp"

#include <fstream>
#include <random>

const int amountOfChunkTemplates = 16;

// SETTINGS
const sf::Vector2i TileSize = {16,16};
const sf::Vector2i WorldChunkSize = {TileSize.x * 32,TileSize.y * 32};

class Chunk : public Node
{
private:
    sf::Vector2i size;
    std::shared_ptr<TileMap> tileMap;

public:

    std::shared_ptr<std::ifstream> loadChunk(std::shared_ptr<sf::Texture> _tileSet);

    Chunk();
    Chunk(std::shared_ptr<sf::Texture> _tileSet);
    ~Chunk();

protected:
};
