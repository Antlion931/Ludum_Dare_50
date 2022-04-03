#include "Chunk.hpp"


Chunk::Chunk(std::shared_ptr<sf::Texture> _tileSet) 
{
    std::random_device randomChunkPicker;
    std::uniform_int_distribution<int> dist(0, amountOfChunkTemplates - 1);
    int randomNumber = dist(randomChunkPicker);

    tileMap.setScale(TileMapScale);
    tileMap.setName("tile map");

    std::ifstream loader("./res/chunkTemplates/chunk" + std::to_string(randomNumber) + ".chunk");

    loader >> size.x;
    loader >> size.y;
    //std::cout << "size.x: " << size.x << ", size.y: " << size.y << std::endl;
    tileMap.loadTileMap(size,_tileSet, TileSize);
    
    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            int tileID;
            loader >> tileID;
            tileMap.setTile({j,i}, tileID - 1);
        }
    }

    WorldChunkSize =
    {TileSize.x * TileMapScale.x * size.x,
    TileSize.y * TileMapScale.y * size.y};

    addChild(std::make_shared<TileMap>(tileMap));
    loader.close();
}


sf::Vector2i Chunk::getWorldChunkSize()
{
    return WorldChunkSize;
}


Chunk::~Chunk()
{

}