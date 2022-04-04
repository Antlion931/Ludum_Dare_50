#include "WorldView.hpp"
#include <cmath>
#include <memory>

WorldView::WorldView(std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet)
: player(_player), currentCenterCoords({100,100}), tileSet(_tileSet)
{
    Objects = std::make_shared<YSort>(YSort());
    Objects->addChild(player);
    //allocateChunk({-1,-1}, currentCenterCoords);
    //allocateChunk({ 0,-1}, currentCenterCoords);
    //allocateChunk({ 1,-1}, currentCenterCoords);
    //allocateChunk({-1, 0}, currentCenterCoords);
    //allocateChunk({ 0, 0}, currentCenterCoords);
    //allocateChunk({ 1, 0}, currentCenterCoords);
    //allocateChunk({-1, 1}, currentCenterCoords);
    //allocateChunk({ 0, 1}, currentCenterCoords);
    //allocateChunk({ 1, 1}, currentCenterCoords);
}


void WorldView::loadStaticObject(std::shared_ptr<std::ifstream> loader)
{
    std::cout << "test\n";
    // format:
    // type spawning_area spawning_area_args amount_lower_bound amount_upper_bound
    // example: tree box 5 5 25 25 10 20
    // will spawn 10 to 20 trees in a box with left top corner at (5,5)
    // and bottom right corner at (25,25)
    std::string ObjectType, spawning_area;
    *loader >> ObjectType;
    *loader >> spawning_area;
    if(spawning_area == "box")
    {
        sf::Vector2i topleft, bottomright;
        *loader >> topleft.x;
        *loader >> topleft.y;
        *loader >> bottomright.x;
        *loader >> bottomright.y;
        int lowerBound, upperBound;
        *loader >> lowerBound;
        *loader >> upperBound;

        std::random_device randomizer;
        std::uniform_int_distribution<int> randAmount(lowerBound, upperBound);
        int amountToSpawn = randAmount(randomizer);
        for(int i = 0; i < amountToSpawn; i++)
        {
            std::uniform_int_distribution<int> xDist(topleft.x, bottomright.x);
            std::uniform_int_distribution<int> yDist(topleft.y, bottomright.y);
            if(ObjectType == "tree")
            {
                Objects->addChild(entityPrefabs.getStaticObject("tree"));
            }
        }
    }
}


void WorldView::onDraw(sf::RenderTarget &target)
{
    // first we draw the chunks
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            sf::Vector2i offsetChunk = {currentCenterCoords.x - i,currentCenterCoords.y - j};
            chunkMap[offsetChunk].draw(target);
        }
    }

    Objects->draw(target);
}

void WorldView::chunkChange(sf::Vector2i newCenterCoords)
{
    // we need to load new chunks
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            allocateChunk({j,i}, newCenterCoords);
        }
    }
    currentCenterCoords = newCenterCoords;
}


void WorldView::onUpdate(const sf::Time& delta)
{
    Objects->update(delta);
    sf::Vector2f playerCoords = player->getGlobalTransform().getPosition();
    sf::Vector2i WorldChunkSize = Chunk().getWorldChunkSize();

    // find which chunk the player is currently in
    sf::Vector2i newCenterCoords;
    newCenterCoords.x = floor(playerCoords.x / WorldChunkSize.x);
    newCenterCoords.y = floor(playerCoords.y / WorldChunkSize.y);

    if( currentCenterCoords != newCenterCoords )
        chunkChange(newCenterCoords);

    Objects->update(delta);
}


void WorldView::onTransform()
{
    Objects->updateTransform(getGlobalTransform());
}


void WorldView::allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo)
{
    sf::Vector2i relativeCoords = {relativeTo.x - chunkCoords.x, relativeTo.y - chunkCoords.y};
    if(chunkMap.count(relativeCoords))
    {
        std::cout << "Found the chunk at: " << relativeCoords.x << ", " << relativeCoords.y << ")\n";
        return;
    }
    Chunk newChunk = Chunk();
    std::shared_ptr<std::ifstream> loader = newChunk.loadChunk(tileSet);

    while(loader->good())
    {
        loadStaticObject(loader);
    }

    loader->close();
    // get relative coords of the chunk
    sf::Vector2i WorldChunkSize = newChunk.getWorldChunkSize();
    newChunk.translate({relativeCoords.x * WorldChunkSize.x, relativeCoords.y * WorldChunkSize.y});

    std::shared_ptr<Chunk> newChunkPtr = std::make_shared<Chunk>(newChunk);

    chunkMap.insert({relativeCoords, newChunk});
}


void WorldView::deallocateChunk(sf::Vector2i chunkCoords)
{

}
