#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Player.hpp"
#include "Toolkit.hpp"

void Player::onUpdate(const sf::Time &delta)
{
    velocity = {0,0};

    if(currentState == DYING)
    {

        currentTime += delta.asSeconds();

        if(currentTime > dyingTime)
        {
            currentTime = 0.0f;
            currentState = DEAD;
            snipersRedDot->setVisible(false);
        }
    }
    else if(currentState == PUNCH)
    {
        currentTime += delta.asSeconds();

        if(currentTime > punchTime)
        {
            currentTime = 0.0f;
            currentState = IDLE;
        }

        const float punchingSlow = 0.5;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocity.x -= speed * punchingSlow;
            isFaceingRight = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            velocity.x += speed * punchingSlow;
            isFaceingRight = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            velocity.y -= speed * punchingSlow;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            velocity.y += speed * punchingSlow;
        }

        if(std::abs(velocity.x) > 0.0f && std::abs(velocity.y > 0.0f))
        {
            velocity.x /= std::sqrt(2);
            velocity.y /= std::sqrt(2);
        }



    }
    else if(currentState != DEAD)
    {
        currentState = IDLE;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocity.x -= speed;
            isFaceingRight = false;
            currentState = RUN;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            velocity.x += speed;
            currentState = RUN;

            isFaceingRight = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            velocity.y -= speed;
            currentState = RUN;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            velocity.y += speed;
            currentState = RUN;

        }

        if(std::abs(velocity.x) > 0.0f && std::abs(velocity.y > 0.0f))
        {
            velocity.x /= std::sqrt(2);
            velocity.y /= std::sqrt(2);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            currentState = PUNCH;
        }
    }

    updateSinpersRedDot(delta);
    updateBody(delta);
}

Player::Player(SoundSystem& soundSystem,sf::Vector2f position, sf::Vector2f size, float _speed, float _dyingTime, float _punchTime) : 
Character(soundSystem, position, size, _speed, _dyingTime), punchTime(_punchTime)
{
    snipersRedDot = std::make_shared<MovingCircle>(MovingCircle(position, 3));
    snipersRedDot->setName("snipers red dot");
    snipersRedDot->circle.setFillColor(sf::Color(255, 0, 0, 255));
    addChild(snipersRedDot);
    
    randHeadPositon();

    snipersRedDot->setTranslation(m_local_transform.getPosition() - sf::Vector2f(100, 100));
}

void Player::onDraw(sf::RenderTarget &target)
{
    target.draw(body,m_global_transform.getTransform());
}

void Player::randHeadPositon()
{
    headPosition = m_local_transform.getPosition();
    headPosition.x -= 100 + rand()%13 - 6;
    headPosition.y -= 100 + rand()%13 - 6 + 20;
}

void Player::updateSinpersRedDot(const sf::Time& delta)
{
    float snipersVelocityMultiplayer = 2;

    if(currentState != IDLE)
    {
        randHeadPositon();
        snipersVelocityMultiplayer = 30;
    }
    else if(std::abs(headPosition.x - snipersRedDot->m_local_transform.getPosition().x) + std::abs(headPosition.y - snipersRedDot->m_local_transform.getPosition().y) < 0.7)
    {
        randHeadPositon();
    }

    sf::Vector2f newVelocity(headPosition - snipersRedDot->m_local_transform.getPosition());
    newVelocity *= snipersVelocityMultiplayer;

    snipersRedDot->setVelocity(newVelocity);
}

Player::Player(SoundSystem& soundSystem)
: Player(soundSystem, {100,100}, {100, 100}, 400, 0.55, 0.4)
{
    setName("Player");
    setIdleAnimation("./res/textures/Player/1-Idle", 0.06);
    setRunAnimation("./res/textures/Player/2-Run", 0.03);
    setPunchAnimation("./res/textures/Player/7-Attack", 0.05);
    setDyingAnimation("./res/textures/Player/12-Hit", 0.05);
    setDeadAnimation("./res/textures/Player/14-DeadGround", 0.1);
    setDyingSoundName("gunShot.wav");
}
