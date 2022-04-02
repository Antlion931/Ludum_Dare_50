#pragma once
#include "Node.hpp"
#include "TileMap.hpp"

#include <fstream>
#include <random>

class Chunk : public Node
{
private:
    sf::Vector2i size;
    TileMap tileMap;

public:
    Chunk(std::shared_ptr<sf::Texture> _tileSet);
    ~Chunk();

protected:
};
