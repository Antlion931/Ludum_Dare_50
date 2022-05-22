#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include "TextureLoader.hpp"

class AnimationManager
{
public:
    AnimationManager(std::string animationDirectoryName, std::map<std::string, float> times, std::string defaultAnimation);
    void setDefault(std::string animation);

    std::shared_ptr<sf::Texture> getTexture();
    sf::IntRect getIntRect();

    void addAnimation(std::string name, float time);

    void play(std::string animation);//it will play animation, overwrite others animations only played by play()
    void playOnce(std::string animation); //it will play animation once, overwrite every other animation
    void update(const sf::Time& delta, bool isFacedRight);

protected:
    void changeAndReset(std::string animation, bool isPlayOnce = false);
    std::string fileName(std::string animation, int index);

    std::map<std::string, float> speeds;
    std::map<std::string, int> amounts;
    
    std::string currentAnimation;
    std::string defaultAnimation;
    int currentIndex;
    float currentTime;

    bool animationPlayOnce;

    std::shared_ptr<TextureLoader> loader;
    sf::IntRect intRect;
};
