#pragma once
#include "Node.hpp"
#include "TileMap.hpp"

#include <fstream>
#include <random>
#include <sstream>
#include <map>
#include <filesystem>


class ChunkTemplateLoader
{
private:
    std::unordered_map<std::string, std::shared_ptr<std::ifstream>> chunkTemplates;
    int size = 0;

public:
    ChunkTemplateLoader();

    std::shared_ptr<std::ifstream> returnChunkMap(std::string name);
    int getChunkTemplatesAmount();
};
