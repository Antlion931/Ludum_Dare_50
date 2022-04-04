#include "Chunk.hpp"
//  x  y      x  y
// [1][0] -> [0][1]

// #X#    ###
// ### -> X##
// ###    ###

sf::Vector2i rotateCoordinates(sf::Vector2i coordinates, int matrixSize, int degrees)
{
    if(degrees == 90)
    {
        // {x, y} -> {n - y - 1, x}
        return {matrixSize - coordinates.y - 1, coordinates.x};
    }
    if(degrees >= 180)
    {
        // {x, y} -> {n - x - 1, n - y - 1}
        return {matrixSize - 1 - coordinates.x, matrixSize - 1 - coordinates.y};
    }
    if(degrees == 270)
    {
        // {x,y} -> {y, n - x - 1}
        return {coordinates.y, matrixSize - coordinates.x - 1};
    }
    return coordinates;
}


Chunk::Chunk()
{
}

std::shared_ptr<std::ifstream> Chunk::loadChunk(std::shared_ptr<sf::Texture> _tileSet)
{
    std::random_device randomChunkPicker;
    std::uniform_int_distribution<int> dist(0, amountOfChunkTemplates - 1);
    int randomNumber = dist(randomChunkPicker);
    std::uniform_int_distribution<int> rotationRandomizer(0,2);
    int rotation = rotationRandomizer(randomChunkPicker);

    tileMap = std::make_shared<TileMap>(TileMap());
    tileMap->setName("tile map");

    //std::shared_ptr<std::ifstream> loader = 
    //make_shared<std::ifstream>(std::ifstream("./res/chunkTemplates/chunk" + std::to_string(randomNumber) + ".chunk"));

    std::shared_ptr<std::ifstream> loader = 
    make_shared<std::ifstream>(std::ifstream("./res/chunkTemplates/chunk0.chunk"));

    // load the tilemap
    *loader >> size.x;
    *loader >> size.y;
    tileMap->loadTileMap(size,_tileSet, TileSize);
    
    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            int tileID;
            *loader >> tileID;
            tileMap->setTile({j,i}, tileID - 1);
        }
    }

    addChild(tileMap);

    return loader;
}


Chunk::~Chunk()
{

}