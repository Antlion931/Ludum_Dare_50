#include "ChunkTemplateLoader.hpp"

ChunkTemplateLoader::ChunkTemplateLoader()
{
    std::ifstream input;
    std::string chunkTemplatesPath = "./res/chunkTemplates";
    for(const auto & chunkTemplate : std::filesystem::directory_iterator(chunkTemplatesPath))
    {
        //input.open(chunkTemplate.path());
        //std::string name = chunkTemplatesPath.substr(chunkTemplatesPath.find_last_of('/')+1);
        //input.close();
        //chunkTemplates[name] = std::make_shared<std::ifstream>(input);
        size++;
    }
    input.close();
}

std::shared_ptr<std::ifstream> ChunkTemplateLoader::returnChunkMap(std::string name)
{
    return chunkTemplates[name];
}

int ChunkTemplateLoader::getChunkTemplatesAmount()
{
    return size;
}