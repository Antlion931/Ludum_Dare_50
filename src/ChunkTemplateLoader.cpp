#include "ChunkTemplateLoader.hpp"

ChunkTemplateLoader::ChunkTemplateLoader()
{
    std::ifstream input;
    std::string chunkTemplatesPath = "./res/chunkTemplates";
    for(const auto & chunkTemplate : std::filesystem::directory_iterator(chunkTemplatesPath))
    {
        input.open(chunkTemplate.path());
        
        input.close();
        size++;
    }
    input.close();
}

std::stringstream ChunkTemplateLoader::returnChunkMap(std::string name)
{

}

int ChunkTemplateLoader::getChunkTemplatesAmount()
{

}