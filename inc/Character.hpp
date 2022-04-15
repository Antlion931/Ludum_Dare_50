#pragma once
#include <iostream>
#include <memory>
#include "DynamicNode.hpp"
#include "Animation.hpp"
#include "SoundSystem.hpp"

class Character : public DynamicNode
{
public:
    Character( sf::Vector2f position, sf::Vector2f size, float _speed, Animation _animation, float _dyingTime);

    void setAnimation(std::string directoryPath, std::vector<float> _speeds, std::vector<int> _animationIndex);

    void setDyingSoundName(std::string _dyingSoundName);

    void offsetTexture(sf::Vector2f offset);

    void kill();
    bool isDead();

    void setSpeed(float _speed){speed = _speed;}
   
protected:

    float dyingTime;
    float currentTime;

    void updateBody(const sf::Time&  delta);

    void onDraw(sf::RenderTarget &target) override;
    sf::RectangleShape body;

    void onUpdate(const sf::Time &delta) override;

    bool isFaceingRight;
    float speed;

    Animation animation;
    std::string dyingSoundName;
    SoundSystem* soundSystem;
};

