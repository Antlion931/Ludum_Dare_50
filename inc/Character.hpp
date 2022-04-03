#pragma once
#include <iostream>
#include <memory>
#include "DynamicNode.hpp"
#include "Animation.hpp"
#include "SoundSystem.hpp"

class Character : public DynamicNode
{
public:
    Character(SoundSystem& _soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, float _dyingTime);
    ~Character();

    void setIdleAnimation(std::string directoryPath, float _animationSpeed);
    void setRunAnimation(std::string directoryPath, float _animationSpeed);
    void setPunchAnimation(std::string directoryPath, float _animationSpeed);
    void setDyingAnimation(std::string directoryPath, float _animationSpeed);
    void setDeadAnimation(std::string directoryPath, float _animationSpeed);
    inline bool isDead()const{return currentAnimation==deadAnimation;};

    void setDyingSoundName(std::string _dyingSoundName);

    void kill();

    
protected:
    enum State
    {
        IDLE,
        RUN,
        PUNCH,
        DYING,
        DEAD
    };


    float dyingTime;
    float currentTime;

    void updateBody(const sf::Time&  delta);

    void onDraw(sf::RenderTarget &target) override;

    std::shared_ptr<Animation> currentAnimation;
    sf::RectangleShape body;

    void onUpdate(const sf::Time &delta) override;
    void setCorrectAnimation();

    bool isFaceingRight;
    State currentState;
    State previousState;
    float speed;

    std::shared_ptr<Animation> idleAnimation;
    std::shared_ptr<Animation> runAnimation;
    std::shared_ptr<Animation> punchAnimation;
    std::shared_ptr<Animation> dyingAnimation;
    std::shared_ptr<Animation> deadAnimation;

    std::string dyingSoundName;
    SoundSystem& soundSystem;
};

