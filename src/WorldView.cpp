#include "WorldView.hpp"
#include <cmath>
#include <memory>

const sf::Vector2f World_View_Scale = {4.f,4.f};
const std::vector<std::string> POSSIBLE_NPCS = {"Female","Male"};

WorldView::WorldView(std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet)
: player(_player), tileSet(_tileSet)
{
    soundSystem = SoundSystem::getInstance();

    allObjects = std::make_shared<std::vector<std::shared_ptr<Node>>>();

    ChunkContainer = std::make_shared<Node>(Node());
    addChild(ChunkContainer);
    ChunkContainer->setScale(World_View_Scale);

    loadedObjects = std::make_shared<YSort>(YSort());
    loadedObjects->addChild(player);
    addChild(loadedObjects);

    player->addCollider(static_layer, static_layer, {0.0, 15.0}, 20.0, "COLLISION");
    player->addCollider(interaction_layer, nullptr, {30.0, 0.0}, {40.0, 70.0}, "KILL");
    player->addCollider(interaction_layer, nullptr, {30.0, 0.0}, {140.0, 100.0}, "TALK");
    player->addCollider(interaction_layer, nullptr, {0.0, 0.0}, {55.0, 55.0}, "100-unit");
    
    chunkChange(currentCenterCoords);
}

void WorldView::loadObject(std::shared_ptr<std::ifstream> loader, sf::Vector2f chunk_pos, bool overrideSpawn)
{
    // format:
    // BOX SPAWNING:
    // type spawning_chance spawning_area_args amount_lower_bound amount_upper_bound
    // example: tree 100 5 5 25 25 10 20

    // LIST SPAWNING:
    // list spawning_chance list_length objects
    // example: list 50 4
    // tree 50 1 1 15 15 10 20
    // tree 30 3 3 25 25 10 20
    // tree 20 5 5 20 25 10 20
    // tree 10 7 7 10 25 10 20
    // will spawn 10 to 20 trees in a box with left top corner at (5,5)
    // and bottom right corner at (25,25)

    std::string ObjectType;
    int spawningChance;
    *loader >> ObjectType;
    *loader >> spawningChance;

    float minDist = 1.0;
    if(ObjectType == "tree") { minDist = 3.0; }
    else if(ObjectType == "building") { minDist = 12.0; }
    else if(ObjectType == "shop") { minDist = 12.0; }
    else if(ObjectType == "umbrella") { minDist = 2; }
    else if(ObjectType == "NPC") { minDist = 2; }
    else if(ObjectType == "bench") { minDist = 2; }
    else if(ObjectType == "lamp_left"){minDist = 7;}
    else if(ObjectType == "lamp_right"){minDist = 7;}
    else if(ObjectType == "hydrant"){minDist = 7;}

    std::random_device randomizer;
    std::uniform_int_distribution<int> spawningChanceGenerator(1, 100);



    if(ObjectType == "list" || ObjectType == "List")
    {
        int listLength;
        *loader >> listLength;
        int chance = spawningChanceGenerator(randomizer);
        bool isListSpawned = overrideSpawn && chance <= spawningChance;
        for(int i = 0; i < listLength; i++)
        {
            loadObject(loader, chunk_pos, isListSpawned);
        }
    }
    else
    {
        sf::Vector2i topleft, bottomright;
        *loader >> topleft.x;
        *loader >> topleft.y;
        *loader >> bottomright.x;
        *loader >> bottomright.y;
        int lowerBound, upperBound;
        *loader >> lowerBound;
        *loader >> upperBound;

        /// SPAWNING CHANCE CHECK
        if (!(overrideSpawn && spawningChanceGenerator(randomizer) <= spawningChance))
        {
            return;
        }


        std::uniform_int_distribution<int> randAmount(lowerBound, upperBound);
        int amountToSpawn = randAmount(randomizer);

        std::vector<sf::Vector2f> spawningPoints;

        sf::Vector2f ScaledTileSize = sf::Vector2f(TileSize) * ChunkContainer->getGlobalTransform().getScale().x;

        float YtoX = float(bottomright.y - topleft.y + 1) / float(bottomright.x - topleft.x + 1);
        float relMinDist = minDist / (bottomright.x - topleft.x + 1) * World_View_Scale.x;

        generatePoints(spawningPoints, amountToSpawn, relMinDist, YtoX);

        for(auto &point : spawningPoints)
        {
            sf::Vector2i intPosition;
            intPosition.x = int(topleft.x * (1.0 - point.x) + bottomright.x * point.x);
            intPosition.y = int(topleft.y * (1.0 - (point.y/YtoX)) + bottomright.y * (point.y/YtoX));

            if (topleft.x == bottomright.x)
                intPosition.x = topleft.x;
            if (topleft.y == bottomright.y)
                intPosition.y = topleft.y;

            if(intPosition.x > bottomright.x)
                std::cout << "AA";

            sf::Vector2f transformedPosition;
            transformedPosition.x = intPosition.x * ScaledTileSize.x + chunk_pos.x;
            transformedPosition.y = intPosition.y * ScaledTileSize.y + chunk_pos.y;

            if(ObjectType == "tree")
            {
                std::shared_ptr<GameObject> tree = std::make_shared<GameObject>(GameObject(transformedPosition, "tree", 1, 1, 1));
                tree->addCollider(static_layer, nullptr, {0.0, 0.0}, 10.0, "COLLISION");
                tree->addCollider(nullptr, interaction_layer, {0.0, 0.0}, 10.0, "INTERACTION");
                tree->setScale(World_View_Scale);
                tree->offsetTexture({0,-20.f});
            }
            else if(ObjectType == "building")
            {
                std::shared_ptr<GameObject> building = std::make_shared<GameObject>(GameObject(transformedPosition, "building", 1, 1, 1));
                building->addCollider(static_layer, nullptr, {0.f, -75}, {180.f,230.f}, "COLLISION");
                building->addCollider(nullptr, interaction_layer, {0.f, -75}, {180.f,230.f}, "INTERACTION");
                building->offsetTexture({0.0, -80.0});
                building->setScale(World_View_Scale);
            }
            else if(ObjectType == "bench_down")
            {
                std::shared_ptr<GameObject> bench = std::make_shared<GameObject>(GameObject(transformedPosition, "bench", 1, 1, 1));
                bench->addCollider(static_layer, nullptr, {0.f, -5.f}, {25.0,10.0}, "COLLISION");
                bench->addCollider(nullptr, interaction_layer, {0.f, -5.f}, {25.0,10.0}, "INTERACTION");
                bench->setName("bench");
                bench->setScale(World_View_Scale);
            }
            else if(ObjectType == "pot")
            {
                std::shared_ptr<GameObject> bench = std::make_shared<GameObject>(GameObject(transformedPosition, "pot", 1, 1, 1));
                bench->addCollider(static_layer, nullptr, {0.f, 5.f}, {35.0,20.0}, "COLLISION");
                bench->addCollider(nullptr, interaction_layer, {0.f, 5.f}, {35.0,20.0}, "INTERACTION");
                bench->setScale(World_View_Scale);
            }
            else if(ObjectType == "hydrant")
            {
                std::shared_ptr<GameObject> hydrant = std::make_shared<GameObject>(GameObject(transformedPosition, "hydrant", 1, 1, 1));
                hydrant->addCollider(static_layer, nullptr, {0.f, 5.f}, 5.0, "COLLISION");
                hydrant->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                hydrant->setScale(World_View_Scale);
            }
            else if(ObjectType == "umbrella")
            {
                std::shared_ptr<GameObject> umbrella = std::make_shared<GameObject>(GameObject(transformedPosition, "umbrella", 1, 1, 1));
                umbrella->addCollider(static_layer, nullptr, {0.f, 5.f}, 5.0, "COLLISION");
                umbrella->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                umbrella->setScale(World_View_Scale);
            }
            else if(ObjectType == "NPC")
            {
                std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(0, POSSIBLE_NPCS.size() - 1);
                std::string random_npc = POSSIBLE_NPCS[dist(randomizer)];
                std::shared_ptr<NPC> npc = std::make_shared<NPC>(NPC(transformedPosition, random_npc, 1, 1, 1, 1, 1));
                npc->addCollider(nullptr, static_layer, {0.f, 5.f}, 5.0, "COLLISION");
                npc->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                npc->setScale(World_View_Scale);
            }
            else if(ObjectType == "bush")
            {
                std::shared_ptr<GameObject> bush = std::make_shared<GameObject>(GameObject(transformedPosition, "bush", 1, 1, 1));
                bush->addCollider(static_layer, nullptr, {0.f, 5.f}, 5.0, "COLLISION");
                bush->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                bush->setScale(World_View_Scale);
            }
            else if(ObjectType == "flowers")
            {
                std::shared_ptr<GameObject> flowers = std::make_shared<GameObject>(GameObject(transformedPosition, "flowers", 1, 1, 1));
                //obiekt->addCollider(static_layer, nullptr, {0.f, 5.f}, 5.0, "COLLISION");
                flowers->addCollider(nullptr, interaction_layer, {0.f, 5.f}, 5.0, "INTERACTION");
                flowers->setScale(World_View_Scale);
            }
            else if(ObjectType == "lamp_left")
            {
                std::shared_ptr<GameObject> lamp = std::make_shared<GameObject>(GameObject(transformedPosition, "lamp_left", 1, 1, 1));
                lamp->addCollider(static_layer, nullptr, {13, 5}, 5.0, "COLLISION");
                lamp->addCollider(nullptr, interaction_layer, {13, 5}, 5.0, "INTERACTION");
                lamp->offsetTexture({6.0, -10.0});
                lamp->setName("lamp");
                lamp->setScale(World_View_Scale);
            }
            else if(ObjectType == "lamp_right")
            {
                std::shared_ptr<GameObject> lamp = std::make_shared<GameObject>(GameObject(transformedPosition, "lamp_right", 1, 1, 1));
                lamp->addCollider(static_layer, nullptr, {-2, 5}, 5.0, "COLLISION");
                lamp->addCollider(nullptr, interaction_layer, {-2, 5}, 5.0, "INTERACTION");
                lamp->offsetTexture({6.0, -10.0});
                lamp->setName("lamp");
                lamp->setScale(World_View_Scale);
            }
            else if(ObjectType == "shop")
            {
                std::shared_ptr<GameObject> shop = std::make_shared<GameObject>(GameObject(transformedPosition, "shop", 1, 1, 1));
                shop->addCollider(static_layer, nullptr, {0.f, -38.f}, {140.0, 90.0}, "COLLISION");
                shop->addCollider(nullptr, interaction_layer, {0.f, -38.f}, {140.0, 90.0}, "INTERACTION");
                shop->offsetTexture({0.0, -40.0});
                shop->setScale(World_View_Scale);
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

void WorldView::reset()
{
    currentCenterCoords = {0,0};
    chunkMap.clear();
    //ChunkContainer->
    allObjects->clear();
}
