#pragma once
#include "Node.hpp"

class TileMap : public Node
{
private:
    sf::Vector2i size;
    std::shared_ptr<sf::Texture> tileSet;

public:
    TileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> tileSet);

    sf::Vector2i getSize();
};