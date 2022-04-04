#include "WorldView.hpp"
#include <cmath>
#include <memory>

const sf::Vector2f World_View_Scale = {4.f,4.f};
const std::vector<std::string> POSSIBLE_NPCS = {"Alchemist", "Archer", "Blacksmith", "Butcher", "Female", "Herald", "King",
    "Mage", "Male", "Merchant", "Princess", "Queen", "Thief"};

WorldView::WorldView(SoundSystem& _soundSystem, std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet)
: player(_player), tileSet(_tileSet), soundSystem(_soundSystem)
{
    allObjects = std::make_shared<std::vector<std::shared_ptr<Node>>>();

    NPCcreator = std::make_shared<NPCCreator>(NPCCreator(static_layer, allObjects, interaction_layer));
    ChunkContainer = std::make_shared<Node>(Node());
    addChild(ChunkContainer);
    ChunkContainer->setScale(World_View_Scale);

    loadedObjects = std::make_shared<YSort>(YSort());
    loadedObjects->addChild(player);
    addChild(loadedObjects);

    player->addCollider(static_layer, static_layer, {0.0, 31.0}, 20.0, "COLLISION");
    player->addCollider(interaction_layer, nullptr, {50.0, 0.0}, {40.0, 70.0}, "KILL");

    chunkChange(currentCenterCoords);
}


void WorldView::loadObject(std::shared_ptr<std::ifstream> loader, sf::Vector2f chunk_pos)
{
    // format:
    // type spawning_area spawning_area_args amount_lower_bound amount_upper_bound
    // example: tree box 5 5 25 25 10 20
    // will spawn 10 to 20 trees in a box with left top corner at (5,5)
    // and bottom right corner at (25,25)
    std::string ObjectType, spawning_area;
    *loader >> ObjectType;
    *loader >> spawning_area;

    float minDist = 0;
    if(ObjectType == "tree") { minDist = 4.0; }
    else if(ObjectType == "building") { minDist = 20.0; }
    else if(ObjectType == "bench_down") { minDist = 6.0; }
    else if(ObjectType == "pot") { minDist = 8.0; }
    else if(ObjectType == "hydrant") { minDist = 6.0; }
    else if(ObjectType == "Umbrella") { minDist = 6.0; }
    else if(ObjectType == "NPC") { minDist = 7.0; }

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

        std::vector<sf::Vector2f> spawningPoints;

        sf::Vector2f ScaledTileSize = sf::Vector2f(TileSize) * ChunkContainer->getGlobalTransform().getScale().x;

        float YtoX = float(bottomright.y - topleft.y + 1) / float(bottomright.x - topleft.x + 1);
        float relMinDist = minDist / (bottomright.x - topleft.x + 1);

        generatePoints(spawningPoints, amountToSpawn, relMinDist, YtoX);

        for(auto &point : spawningPoints)
        {
            sf::Vector2f transformedPosition = point;
            transformedPosition.x = (topleft.x * (1.0 - point.x) + bottomright.x * point.x) * ScaledTileSize.x + chunk_pos.x;
            transformedPosition.y = (topleft.y * (1.0 - point.y) + bottomright.y * point.y) * ScaledTileSize.y + chunk_pos.y;

            std::cout << "Spawning at: (" << transformedPosition.x << ", " << transformedPosition.y << ")\n";
            if(ObjectType == "tree")
            {
                std::shared_ptr<NPC> tree = NPCcreator->makeNPC("Tree", soundSystem, transformedPosition, {32,48}, NON_MOVE_NPC);
                tree->addCollider(static_layer, nullptr, {0.0, 0.0}, 10.0, "COLLISION");
                tree->addCollider(nullptr, interaction_layer, {0.0, 0.0}, 10.0, "INTERACTION");
                tree->setScale(World_View_Scale);
                tree->offsetTexture({0,-20.f});
                /*auto t = entityPrefabs.getStaticObject("tree");
                allObjects.push_back(t);*/
                //tree.translate(chunk_pos + sf::Vector2f(xDist(randomizer),yDist(randomizer)) * ScaledTileSize.x);
            }
            else if(ObjectType == "building")
            {
                std::shared_ptr<NPC> building = NPCcreator->makeNPC("Building", soundSystem, transformedPosition, {180,240}, NON_MOVE_NPC);
                building->addCollider(static_layer, nullptr, {0.f, 5.f}, {180.f,212.f}, "COLLISION");
                building->addCollider(nullptr, interaction_layer, {0.f, 5.f}, {180.f,212.f}, "INTERACTION");
                //building->right
                building->setScale(World_View_Scale);
            }
            else if(ObjectType == "bench_down")
            {
                std::shared_ptr<NPC> bench = NPCcreator->makeNPC("Bench_Down", soundSystem, transformedPosition, {40.0,20.0}, NON_MOVE_NPC);
                bench->addCollider(static_layer, nullptr, {0.f, 5.f}, {40.0,20.0}, "COLLISION");
                bench->addCollider(nullptr, interaction_layer, {0.f, 5.f}, {40.0,20.0}, "INTERACTION");
                //building->right
                bench->setScale(World_View_Scale);
            }
            else if(ObjectType == "pot")
            {
                std::shared_ptr<NPC> bench = NPCcreator->makeNPC("Pot", soundSystem, transformedPosition, {45.0,30.0}, NON_MOVE_NPC);
                bench->addCollider(static_layer, nullptr, {0.f, 5.f}, {35.0,20.0}, "COLLISION");
                bench->addCollider(nullptr, interaction_layer, {0.f, 5.f}, {35.0,20.0}, "INTERACTION");
                //building->right
                bench->setScale(World_View_Scale);
            }
            else if(ObjectType == "hydrant")
            {
                std::shared_ptr<NPC> obiekt = NPCcreator->makeNPC("Hydrant", soundSystem, transformedPosition, {16.0,16.0}, NON_MOVE_NPC);
                obiekt->addCollider(static_layer, nullptr, {0.f, 5.f}, 5.0, "COLLISION");
                obiekt->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                //building->right
                obiekt->setScale(World_View_Scale);
            }
            else if(ObjectType == "umbrella")
            {
                std::shared_ptr<NPC> obiekt = NPCcreator->makeNPC("Umbrella", soundSystem, transformedPosition, {30.0,45.0}, NON_MOVE_NPC);
                obiekt->addCollider(static_layer, nullptr, {0.f, 5.f}, 5.0, "COLLISION");
                obiekt->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                //building->right
                obiekt->setScale(World_View_Scale);
            }
            else if(ObjectType == "NPC")
            {
                std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(0, POSSIBLE_NPCS.size() - 1);
                std::string random_npc = POSSIBLE_NPCS[dist(randomizer)];
                std::shared_ptr<NPC> obiekt = NPCcreator->makeNPC(random_npc, soundSystem, transformedPosition, {50.0,50.0}, STANDARD_NPC);
                obiekt->addCollider(nullptr, static_layer, {0.f, 5.f}, 5.0, "COLLISION");
                obiekt->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                //building->right
                obiekt->setScale(World_View_Scale);
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
    for(auto object : *allObjects.get())
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
        loadObject(loader, trans * ChunkContainer->getGlobalTransform().getScale().x);
    }
    loader->close();


    ChunkContainer->addChild(chunk);
    chunkMap.insert({relativeCoords, chunk});
}


void WorldView::deallocateChunk(sf::Vector2i chunkCoords)
{

}
