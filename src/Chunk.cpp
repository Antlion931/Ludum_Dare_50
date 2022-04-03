#include "Chunk.hpp"


Chunk::Chunk()
{
    
}


Chunk::Chunk(std::shared_ptr<sf::Texture> _tileSet) 
{
    loadChunk(_tileSet);
}


void Chunk::loadChunk(std::shared_ptr<sf::Texture> _tileSet)
{
    std::random_device randomChunkPicker;
    std::uniform_int_distribution<int> dist(0, amountOfChunkTemplates - 1);
    int randomNumber = dist(randomChunkPicker);

    tileMap.setScale(TileMapScale);
    tileMap.setName("tile map");

    std::ifstream loader("./res/chunkTemplates/chunk" + std::to_string(randomNumber) + ".chunk");

    // load the tilemap
    loader >> size.x;
    loader >> size.y;
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

    // load the NPCS
    while(loader.good())
    {
        loadNPC(loader);
    }

    loader.close();
}


void Chunk::loadNPC(std::ifstream &loader)
{
    // format:
    // type spawning_area spawning_area_args amount_lower_bound amount_upper_bound
    // example: tree box 5 5 25 25 10 20
    // will spawn 10 to 20 trees in a box with left top corner at (5,5)
    // and bottom right corner at (25,25)
    std::string NPCtype, spawning_area;
    loader >> NPCtype;
    loader >> spawning_area;
    if(spawning_area == "box")
    {
        sf::Vector2i topleft, bottomright;
        loader >> topleft.x;
        loader >> topleft.y;
        loader >> bottomright.x;
        loader >> bottomright.y;
        int lowerBound, upperBound;
        loader >> lowerBound;
        loader >> upperBound;

        std::random_device randomizer;
        std::uniform_int_distribution<int> randAmount(lowerBound, upperBound);
        int amountToSpawn = randAmount(randomizer);
        for(int i = 0; i < amountToSpawn; i++)
        {
            std::uniform_int_distribution<int> xDist(topleft.x, bottomright.x);
            std::uniform_int_distribution<int> yDist(topleft.y, bottomright.y);
            if(NPCtype == "tree")
            {
                //std::shared_ptr<NPC> tree = std::make_shared<NPC>(
                //    NPC(SoundSystem);
                //);
                //tree->setUpByName("tree");
            }
        }
    }
}


sf::Vector2i Chunk::getWorldChunkSize()
{
    return WorldChunkSize;
}


Chunk::~Chunk()
{

}