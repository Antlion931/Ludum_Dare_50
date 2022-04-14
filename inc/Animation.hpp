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
    Animation(std::shared_ptr<TextureLoader> _loader, std::vector<float> _speeds, std::vector<int> _animationIndex);
    Animation(std::string texturesDirectory, std::vector<float> _speeds, std::vector<int> _animationIndex);
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

    std::shared_ptr<TextureLoader> loader;
    std::string fileFormat;
    sf::IntRect intRect;
};
