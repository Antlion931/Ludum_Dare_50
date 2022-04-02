#pragma once
#include "Node.hpp"

class TileMap : public Node
{
private:
    sf::Vector2i size;
    std::shared_ptr<sf::Texture> tileSet;
    sf::VertexArray vertices;
    sf::Vector2i tileSize = {16,16};

public:
    TileMap(sf::Vector2i _size, std::shared_ptr<sf::Texture> tileSet);

    void setTile(sf::Vector2i position, unsigned int tileID);

    sf::Vector2i getSize();

    std::shared_ptr<sf::Texture> getTileSet();

protected:
    void onDraw(sf::RenderTarget &target) const override;
};