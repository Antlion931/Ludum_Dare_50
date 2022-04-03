#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include "TextureLoader.hpp"

enum AnimationType
{
IDLE,
RUN,
DYING,
DEAD,
PUNCHING
};

class Animation
{
public:
    Animation(std::string directoryPath, std::vector<float> _speeds, std::vector<int> _animationIndex);
    std::shared_ptr<sf::Texture> getTexture();
    sf::IntRect getIntRect();
    void changeAnimation(AnimationType newAnimationType);
    AnimationType getCurrentAnimation();
    void update(const sf::Time& delta, bool isFacedRight);
    void reset();

protected:
    std::vector<float> speeds;
    std::vector<int> animationIndex;
    AnimationType currentAnimation;
    int currentIndex;
    float currentTime;

    TextureLoader loader;
    std::string fileFormat;
    sf::IntRect intRect;
};
