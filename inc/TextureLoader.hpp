#pragma once
#include <iostream>
#include<SFML/Graphics/Texture.hpp>
#include<vector>
class TextureLoader{
    public:
        TextureLoader(std::string _directoryPath){
            directoryPath = _directoryPath;
            loadTextures();
        }
        sf::Texture* returnTexture(int id);
        int getAmountOfTestures();

    private:
        void loadTextures();
        std::vector<sf::Texture> textures;
        std::string directoryPath;
        int textureCount = 0;
};