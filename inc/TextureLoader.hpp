#pragma once
#include <iostream>
#include<SFML/Graphics/Texture.hpp>
#include<map>
#include <memory>
#include<string>
class TextureLoader{
    public:
        TextureLoader(std::string _directoryPath){
            directoryPath = _directoryPath;
            loadTextures();
        }
        std::shared_ptr<sf::Texture> returnTexture(std::string _fileName);
        int getAmountOfTextures();

    private:
        void loadTextures();
        std::map<std::string,std::shared_ptr<sf::Texture>> textures;
        std::string directoryPath;
};