#include "TileMap.hpp"


TileMap::TileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> _tileSet) : size(_size), tileSet(_tileSet)
{
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(size.x * size.y * 4);
    for (unsigned int i = 0; i < size.x; ++i)
        for (unsigned int j = 0; j < size.y; ++j)
        {
            sf::Vertex *quad = &vertices[(i + j * size.x) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // ustaw puste tekstury
            quad[0].texCoords = sf::Vector2f(); // left top
            quad[1].texCoords = sf::Vector2f(); // right top
            quad[2].texCoords = sf::Vector2f(); // right bottom
            quad[3].texCoords = sf::Vector2f(); // left bottom
        }
}


void TileMap::setTile(sf::Vector2i position, unsigned int tileID)
{
    int tu = tileID % size.x; // 2
    int tv = tileID / size.x; // 0

    sf::Vertex *quad = &vertices[(position.x + position.y * size.x) * 4];

    quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y); // left top
    quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y); // right top
    quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y); // right bottom
    quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y); // left bottom
}


sf::Vector2i TileMap::getSize()
{
    return size;
}


std::shared_ptr<sf::Texture> TileMap::getTileSet()
{
    return tileSet;
}


void TileMap::onDraw(sf::RenderTarget &target) const
{
    sf::RenderStates state;
    state.texture = tileSet.get();
    state.transform = m_global_transform.getTransform();
    target.draw(vertices, state);
}
