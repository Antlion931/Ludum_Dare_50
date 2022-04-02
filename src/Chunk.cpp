#include "Chunk.hpp"

const int amountOfChunkTemplates = 1;


Chunk::Chunk(std::shared_ptr<sf::Texture> _tileSet) 
{
    std::random_device randomChunkPicker;
    std::uniform_int_distribution<int> dist(0, amountOfChunkTemplates - 1);
    int randomNumber = dist(randomChunkPicker);

    std::ifstream loader("./res/chunkTemplates/chunk" + std::to_string(randomNumber) + ".chunk");

    loader >> size.x;
    loader >> size.y;
    std::cout << "size.x: " << size.x << ", size.y: " << size.y << std::endl;
    tileMap.loadTileMap(size,_tileSet);
    
    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            int tileID;
            loader >> tileID;
            std::cout << "TileID: " << tileID << std::endl;
            tileMap.setTile({j,i}, tileID - 1);
        }
    }

    addChild(std::make_shared<TileMap>(tileMap));
    loader.close();
}

Chunk::~Chunk()
{

}