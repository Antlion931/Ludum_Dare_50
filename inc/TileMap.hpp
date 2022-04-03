#pragma once
#include "Node.hpp"

class TileMap : public Node
{
private:
    sf::Vector2i size;
    std::shared_ptr<sf::Texture> tileSet;
    sf::VertexArray vertices;
    sf::Vector2i tileSize;

public:
    TileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> tileSet, sf::Vector2i _TileSize = {16,16});
    TileMap(sf::Vector2i _TileSize = {16,16});

    void setTile(sf::Vector2i position, unsigned int tileID);
    void loadTileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> tileSet, sf::Vector2i _TileSize = {16,16});

    sf::Vector2i getSize();

    std::shared_ptr<sf::Texture> getTileSet();

protected:
    void onDraw(sf::RenderTarget &target) override;
};