#include "WorldView.hpp"
#include <cmath>
#include <memory>

WorldView::WorldView(SoundSystem& _soundSystem, std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet)
: player(_player), tileSet(_tileSet), NPCcreator(static_layer, allObjects, interaction_layer),
soundSystem(_soundSystem)
{
    ChunkContainer = std::make_shared<Node>(Node());
    addChild(ChunkContainer);
    ChunkContainer->setScale({0.5f,0.5f});

    loadedObjects = std::make_shared<YSort>(YSort());
    loadedObjects->addChild(player);
    addChild(loadedObjects);


    player->addCollider(static_layer, static_layer, {0.0, 31.0}, 20.0);
    player->addCollider(interaction_layer, nullptr, {50.0, 0.0}, {40.0, 70.0}, "kill-box");

    NPCcreator.makeNPC("Alchemist", soundSystem, {400,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Archer", soundSystem, {500,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Blacksmith", soundSystem, {600,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Butcher", soundSystem, {700,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Female", soundSystem, {800,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Herald", soundSystem, {900,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("King", soundSystem, {1000,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Mage", soundSystem, {1100,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Male", soundSystem, {1200,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Merchant", soundSystem, {1300,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Princess", soundSystem, {1400,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Queen", soundSystem, {1500,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Thief", soundSystem, {1600,400}, {100,100}, NPCAnimationSequences);
    NPCcreator.makeNPC("Tree", soundSystem, {1600,400}, {100,100}, NonAnimationSequences);

    chunkChange(currentCenterCoords);
}


void WorldView::loadStaticObject(std::shared_ptr<std::ifstream> loader, sf::Vector2f chunk_pos)
{
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
                std::cout << "Added a new tree\n";
                sf::Vector2f ScaledTileSize = sf::Vector2f(TileSize) * ChunkContainer->getGlobalTransform().getScale().x;
                std::shared_ptr<NPC> tree = NPCcreator.makeNPC("Tree", soundSystem, {chunk_pos.x + xDist(randomizer) * ScaledTileSize.x,
                chunk_pos.y + yDist(randomizer) * ScaledTileSize.y}, {100,100}, NonAnimationSequences);
                /*auto t = entityPrefabs.getStaticObject("tree");
                allObjects.push_back(t);*/
                tree->setSpeed(0.f);
                //tree.translate(chunk_pos + sf::Vector2f(xDist(randomizer),yDist(randomizer)) * ScaledTileSize.x);
            }
        }
    }
}

void WorldView::chunkChange(sf::Vector2i newCenterCoords)
{
    // we need to load new chunks
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(chunkMap.contains({newCenterCoords.x-j,newCenterCoords.y-i}))
            {
                if(!ChunkContainer->isChild(chunkMap[{newCenterCoords.x-j,newCenterCoords.y-i}]))
                {
                    allocateChunk({j,i}, newCenterCoords);
                }
            }
            else
                allocateChunk({j,i}, newCenterCoords);
            
        }
    }
    // deactivate old tilemaps
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(abs(newCenterCoords.x - (currentCenterCoords.x - j)) > 1 || 
               abs(newCenterCoords.y - (currentCenterCoords.y - i)) > 1)
            {
                ChunkContainer->removeChild(chunkMap[{currentCenterCoords.x - j,currentCenterCoords.y - i}]);
            }
            //if(chunkMap.contains({currentCenterCoords.x - j,currentCenterCoords.y - i}))
            //ChunkContainer->removeChild(chunkMap[{currentCenterCoords.x - j,currentCenterCoords.y - i}]);
        }
    }
    // allocate/activate and deactivate entities
    sf::Vector2f centerOfCurrentChunk = {newCenterCoords.x * ScaledWorldChunkSize.x + 0.5f * ScaledWorldChunkSize.x,
         newCenterCoords.y * ScaledWorldChunkSize.y + 0.5f * ScaledWorldChunkSize.y};
    //std::cout << "Current Chunk Coords: (" << currentCenterCoords.x << ", " << currentCenterCoords.y << ")\n";
    //std::cout << "Chunk size: (" << ScaledWorldChunkSize.x << ", " << ScaledWorldChunkSize.y << ")\n";
    //std::cout << "Center of current chink: (" << centerOfCurrentChunk.x << ", " << centerOfCurrentChunk.y << ")\n";
    for(auto object : allObjects)
    {
        sf::Vector2f objectCoords = object->getGlobalTransform().getPosition();
        // we check whether the object is in the worldview 
        if(abs(centerOfCurrentChunk.x - objectCoords.x ) > 1.5 * ScaledWorldChunkSize.x ||
           abs(centerOfCurrentChunk.y - objectCoords.y ) > 1.5 * ScaledWorldChunkSize.y)
        { 
            // we remove the object
            if(loadedObjects->isChild(object))
            {
                loadedObjects->removeChild(object);
            }
        }
        else
        {
            // we add the object
            if(!loadedObjects->isChild(object))
            {
                loadedObjects->addChild(object);
            }
        }
    }


    currentCenterCoords = newCenterCoords;
}

void WorldView::onUpdate(const sf::Time& delta)
{
    sf::Vector2f playerCoords = player->getGlobalTransform().getPosition();
    ScaledWorldChunkSize = sf::Vector2f(WorldChunkSize) * ChunkContainer->getGlobalTransform().getScale().x;

    // find which chunk the player is currently in
    sf::Vector2i newCenterCoords;
    newCenterCoords.x = floor(playerCoords.x / ScaledWorldChunkSize.x);
    newCenterCoords.y = floor(playerCoords.y / ScaledWorldChunkSize.y);

    if( currentCenterCoords != newCenterCoords )
        chunkChange(newCenterCoords);

    loadedObjects->update(delta);
}

void WorldView::allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo)
{
    sf::Vector2i relativeCoords = {relativeTo.x - chunkCoords.x, relativeTo.y - chunkCoords.y};
    if(chunkMap.contains(relativeCoords))
    {
        ChunkContainer->addChild(chunkMap[{relativeCoords}]);
        //std::cout << "Found the chunk at: " << relativeCoords.x << ", " << relativeCoords.y << ")\n";
        return;
    }
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(Chunk());
    chunk->setName("Chunk");
    std::shared_ptr<std::ifstream> loader = chunk->loadChunk(tileSet);

    // while(loader->good())
    // {
    // }

    // get global coords of the chunk
    sf::Vector2f trans = {relativeCoords.x * WorldChunkSize.x, relativeCoords.y * WorldChunkSize.y};
    chunk->translate(trans);

    while(loader->good())
    {
        loadStaticObject(loader, trans * ChunkContainer->getGlobalTransform().getScale().x);
    }
    loader->close();


    ChunkContainer->addChild(chunk);
    chunkMap.insert({relativeCoords, chunk});
}


void WorldView::deallocateChunk(sf::Vector2i chunkCoords)
{

}
