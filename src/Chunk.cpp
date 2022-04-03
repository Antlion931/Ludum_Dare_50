#include "Chunk.hpp"


Chunk::Chunk()
{
    
}

std::shared_ptr<std::ifstream> Chunk::loadChunk(std::shared_ptr<sf::Texture> _tileSet)
{
    std::random_device randomChunkPicker;
    std::uniform_int_distribution<int> dist(0, amountOfChunkTemplates - 1);
    int randomNumber = dist(randomChunkPicker);

    tileMap.setScale(TileMapScale);
    tileMap.setName("tile map");

    std::shared_ptr<std::ifstream> loader = 
    make_shared<std::ifstream>(std::ifstream("./res/chunkTemplates/chunk" + std::to_string(randomNumber) + ".chunk"));

    // load the tilemap
    *loader >> size.x;
    *loader >> size.y;
    tileMap.loadTileMap(size,_tileSet, TileSize);
    
    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            int tileID;
            *loader >> tileID;
            tileMap.setTile({j,i}, tileID - 1);
        }
    }

    WorldChunkSize =
    {TileSize.x * TileMapScale.x * size.x,
    TileSize.y * TileMapScale.y * size.y};

    addChild(std::make_shared<TileMap>(tileMap));

    return loader;
}


sf::Vector2i Chunk::getWorldChunkSize()
{
    return WorldChunkSize;
}


Chunk::~Chunk()
{

}