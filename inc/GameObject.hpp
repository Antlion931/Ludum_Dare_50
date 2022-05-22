#pragma once
#include <iostream>
#include <memory>
#include "DynamicNode.hpp"
#include "AnimationManager.hpp"
#include "SoundSystem.hpp"

class GameObject : public DynamicNode
{
public:
    GameObject(sf::Vector2f position, std::string animationDirectoryName, float idleTime, float dyingTime, float deadTime);

    void setDyingSoundName(std::string _dyingSoundName);
    void offsetTexture(sf::Vector2f offset);

    void kill();
    bool isDead();

    void setSpeed(float _speed){speed = _speed;}
   
protected:

    bool dead = false;
    bool dying = false;
    bool isFaceingRight;
    float speed;

    sf::RectangleShape body;
    AnimationManager animationManager;
    std::string dyingSoundName;
    SoundSystem* soundSystem;

    void updateBody(const sf::Time&  delta);

    void onDraw(sf::RenderTarget &target) override;

    void onUpdate(const sf::Time &delta) override;
};

