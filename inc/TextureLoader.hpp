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
        
        TextureLoader(TextureLoader& loader);
        TextureLoader()
        {
            directoryPath = "BROKEN!";
        }
        std::shared_ptr<sf::Texture> returnTexture(std::string fileName);
        bool checkIfThereIs(std::string fileName);
        int getAmountOfTextures();

    private:
        static std::string fileFormat;
        void loadTextures();
        std::map<std::string,std::shared_ptr<sf::Texture>> textures;
        std::string directoryPath;
};
