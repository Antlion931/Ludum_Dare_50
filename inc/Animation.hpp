#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureLoader.hpp"

class Animation
{
public:
    Animation(std::string directoryPath, float _animationSpeed);
    sf::Texture* getTexture();
    sf::IntRect getIntRect();
    void update(const sf::Time& delta, bool isFacedRight);
    void reset();

protected:

    std::string currentIndex;
    float currentTime;
    float animationSpeed;
    TextureLoader loader;
    sf::IntRect intRect;
};
