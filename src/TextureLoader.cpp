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
        textures.insert({str,texture});
        std::cout << "Loaded Texture with id: " << str << std::endl;
    }
};

sf::Texture* TextureLoader::returnTexture(std::string _fileName){
    return &textures.at(_fileName);
};

int TextureLoader::getAmountOfTextures()
{
    return textures.size();
}