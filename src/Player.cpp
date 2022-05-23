#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "DebugFlag.hpp"
#include "Player.hpp"
#include "Toolkit.hpp"

void Player::onUpdate(const sf::Time &delta)
{
    velocity = {0,0};
    if(isFaceingRight)
    {
            colliders["KILL"]->setTranslation({30.f,0.f});
            colliders["TALK"]->setTranslation({30.f,0.f});
    }
    else
    {
        colliders["KILL"]->setTranslation({-30.f,0.f});
        colliders["TALK"]->setTranslation({-30.f,0.f});
    }

    if(dying || dead)
    {
        snipersRedDot->setVisible(false);
    }
    if(punching)
    {   
        colliders["KILL"]->setActive(true);
        currentTime += delta.asSeconds();
        if(currentTime > punchTime)
        {
            colliders["KILL"]->setActive(false);
            currentTime = 0.0f;
        }

        const float punchingSlow = 0.5;
        updateVelocty(delta * punchingSlow);
    }
    else
    {
        updateVelocty(delta);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            #if(DEBUG)
            colliders["100-unit"]->setActive(false);
            #endif
            colliders["TALK"]->setActive(true);
        }else{
            #if(DEBUG)
            colliders["100-unit"]->setActive(true);
            #endif
            colliders["TALK"]->setActive(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            #if(DEBUG)
            colliders["100-unit"]->setActive(false);
            #endif
            colliders["KILL"]->setActive(true);
            animationManager.playOnce(PUNCH);
            soundSystem->playSound(punchSoundDirectory);
        }
        else 
        {
            colliders["KILL"]->setActive(false);
            #if(DEBUG)
            colliders["100-unit"]->setActive(true);
            #endif
            if(std::abs(velocity.x) > 0.0f || std::abs(velocity.y) > 0.0f)
            {
                animationManager.play(RUN);
            }
            else
            {
                animationManager.play(IDLE);
            }
        }
    }

    if(isFaceingRight)
        colliders["KILL"]->setTranslation({50.0,0.0});
    else
        colliders["KILL"]->setTranslation({-50.0,0.0});
        
    updateSinpersRedDot(delta);
    updateBody(delta);
}

Player::Player(sf::Vector2f position, std::string animationDirectoryName, float idleTime, float dyingTime, float deadTime, float runTime, float _punchTime, float _speed) : 
GameObject(position, animationDirectoryName, idleTime, dyingTime, deadTime), speed(_speed), punchTime(_punchTime)
{
    offsetTexture({0.0, -20.0});

    animationManager.addAnimation(RUN, runTime);
    animationManager.addAnimation(PUNCH, _punchTime);

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
    headPosition.x -= rand()%13 - 6;
    headPosition.y -= rand()%13 - 6 + 20;
}

void Player::updateSinpersRedDot(const sf::Time& delta)
{
    float snipersVelocityMultiplayer = 2;

    if(dot(velocity, velocity) > 0.0f)
    {
        randHeadPositon();
        snipersVelocityMultiplayer = 40;
    }
    else if(std::abs(headPosition.x - snipersRedDot->m_local_transform.getPosition().x) + std::abs(headPosition.y - snipersRedDot->m_local_transform.getPosition().y) < 0.7)
    {
        randHeadPositon();
    }

    sf::Vector2f newVelocity(headPosition - snipersRedDot->m_local_transform.getPosition());
    newVelocity *= snipersVelocityMultiplayer;

    snipersRedDot->setVelocity(newVelocity);
}

#if(DEBUG)
Player::Player()
: Player ({100,100}, "Player", 1, 1, 1, 1, 1, 800)
{
    setName("player");
    setDyingSoundName("gunShotMono.wav");
    punchSoundDirectory = "punch.wav";
}
#else
Player::Player()
: Player ({100,100}, "Player", 1, 1, 1, 1, 1, 300)
{
    setName("player");
    setDyingSoundName("gunShotMono.wav");
    punchSoundDirectory = "punch.wav";
}
#endif

void Player::updateVelocty(const sf::Time& delta)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;
        isFaceingRight = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
        isFaceingRight = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity.y -= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y += speed;
    }

    if(std::abs(velocity.x) > 0.0f && std::abs(velocity.y > 0.0f))
    {
        velocity.x /= std::sqrt(2);
        velocity.y /= std::sqrt(2);
    }
}
