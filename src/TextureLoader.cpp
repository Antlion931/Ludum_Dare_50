#include"TextureLoader.hpp"
#include<SFML/Graphics/Texture.hpp>
#include<string>
#include<iostream>
#include<filesystem>

void TextureLoader::loadTextures(){
    for(const auto &entry: std::filesystem::directory_iterator(directoryPath)){
        sf::Texture texture;
        if(!texture.loadFromFile(entry.path())){
            std::cerr<<"Error while loading audio!"<<std::endl;
            continue;
        };
        std::string str = entry.path();
        str.erase(0,directoryPath.length()+1);
        textures.insert({str,std::make_shared<sf::Texture>(texture)});
        //std::cout << "Loaded Texture with id: " << str << std::endl;
    }
}

TextureLoader::TextureLoader(std::shared_ptr<TextureLoader> loader)
{
    directoryPath = loader->directoryPath;
    textures = loader->textures;
}

std::shared_ptr<sf::Texture> TextureLoader::returnTexture(std::string _fileName){
    //std::cout << "return texture " + _fileName << std::endl;
    return textures.at(_fileName);
}

int TextureLoader::getAmountOfTextures()
{
    return textures.size();
}