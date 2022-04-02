#include "TileMap.hpp"


TileMap::TileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> _tileSet) : size(_size), tileSet(_tileSet)
{
    
}


sf::Vector2i TileMap::getSize()
{
    return size;
}