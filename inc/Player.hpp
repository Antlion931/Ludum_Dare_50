#pragma once
#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "SoundSystem.hpp"
#include "MovingCircle.hpp"

const std::string PUNCH = "punch";

class Player : public GameObject
{
public:
    Player(sf::Vector2f position, std::string animationDirectoryName, float idleTime, float dyingTime, float deadTime, float runTime, float _punchTime, float _speed);
    Player();

protected:

    std::string punchSoundDirectory; 

    std::shared_ptr<MovingCircle> snipersRedDot;
    sf::Vector2f headPosition;

    void onDraw(sf::RenderTarget &target) override;
    void onUpdate(const sf::Time &delta) override;

private:
    float currentTime;
    float speed;
    float punchTime;
    bool punching;
    void randHeadPositon();
    void updateSinpersRedDot(const sf::Time& delta);
    void updateVelocty(const sf::Time& delta);
};
