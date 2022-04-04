#pragma once
#include "Node.hpp"
#include "Chunk.hpp"
#include "Y-sort.hpp"
#include "Player.hpp"
#include "StaticNode.hpp"
#include "EntityPrefabs.hpp"
#include "ChunkTemplateLoader.hpp"
#include <unordered_map>
#include <map>


class WorldView : public Node
{
private:
    struct KeyHasher
    {
        std::size_t operator()(const sf::Vector2i& k) const
        {
            return ((std::hash<int>()(k.x) ^ (std::hash<int>()(k.y) << 1)) >> 1);
        }
    };

    std::shared_ptr<sf::Texture> tileSet;

    EntityPrefabs entityPrefabs;
    
    std::unordered_map<sf::Vector2i, std::shared_ptr<Chunk>, KeyHasher> chunkMap;
    std::shared_ptr<Node> ChunkContainer;

    std::shared_ptr<CollisionLayer> static_layer = std::make_shared<CollisionLayer>(CollisionLayer());;
    std::shared_ptr<CollisionLayer> interaction_layer = std::make_shared<CollisionLayer>(CollisionLayer());;
    std::shared_ptr<NPCCreator> NPCcreator;

    std::shared_ptr<Player> player;
    sf::Vector2i currentCenterCoords = {0,0};

    // to change
    sf::Vector2f ScaledWorldChunkSize = {256 * 6,256 * 6};

    void chunkChange(sf::Vector2i chunkCoords);

    void allocateChunk(sf::Vector2i chunkCoords, sf::Vector2i relativeTo);
    void deallocateChunk(sf::Vector2i chunkCoords);

    void loadStaticObject(std::shared_ptr<std::ifstream> loader, sf::Vector2f chunk_pos);

public:
    std::shared_ptr<YSort> loadedObjects;
    std::shared_ptr<std::vector<std::shared_ptr<Node>>> allObjects;

    SoundSystem& soundSystem;

    WorldView(SoundSystem& _soundSystem, std::shared_ptr<Player> _player, std::shared_ptr<sf::Texture> _tileSet);

protected:
    void onUpdate(const sf::Time& delta) override;
};