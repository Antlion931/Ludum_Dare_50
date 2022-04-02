#pragma once
#include "Node.hpp"

const int TileSize = 16;


class TileMap : public Node
{
private:
    sf::Vector2i size;
    std::shared_ptr<sf::Texture> tileSet;
    sf::VertexArray vertices;
    sf::Vector2i tileSize = {TileSize,TileSize};

public:
    TileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> tileSet);
    TileMap();

    void setTile(sf::Vector2i position, unsigned int tileID);
    void loadTileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> tileSet);

    sf::Vector2i getSize();

    std::shared_ptr<sf::Texture> getTileSet();

protected:
    void onDraw(sf::RenderTarget &target) const override;
};