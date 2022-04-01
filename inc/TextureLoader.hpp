#pragma once
#include<SFML/Graphics/Texture.hpp>
#include<vector>
class TextureLoader{
    public:
        TextureLoader(){
            loadTextures();
        }
        void loadTextures();
        sf::Texture* returnTexture(int id);

    private:
        std::vector<sf::Texture> textures;
        int textureCount = 0;
};