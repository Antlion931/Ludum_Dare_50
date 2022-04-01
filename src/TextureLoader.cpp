#include"TextureLoader.hpp"
#include<SFML/Graphics/Texture.hpp>
#include<string>
#include<iostream>
#include<filesystem>
namespace fs = std::filesystem;

void TextureLoader::loadTextures(){

    std::cout << "      | Loading Textures |" << std::endl;
    std::string path = "./assets/textures/";
    for(const auto &entry: fs::directory_iterator(path)){
        std::cout << "Loading: " << entry.path() << " | id: "<< textureCount << std::endl;
        sf::Texture texture;
        if(!texture.loadFromFile(entry.path())){
            std::cerr << "Problem occured while loading texture ;<";
            continue;
        }
        textures.push_back(texture);
        textureCount++;
    }
};

sf::Texture* TextureLoader::returnTexture(int id){ 
    return &textures.at(id);
};