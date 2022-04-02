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

    
    translate({velocity.x * delta.asSeconds() , velocity.y * delta.asSeconds()});
    setCorrectAnimation();

    currentAnimation->update(delta, isFaceingRight);

    body.setTexture(currentAnimation -> getTexture());
    body.setTextureRect(currentAnimation->getIntRect());

    float snipersVelocityMultiplayer = 5;

    if(currentState != IDLE)
    {
        headPosition.x = m_local_transform.getPosition().x + body.getSize().x * 1.5 + rand()%17 - 8;
        headPosition.y = m_local_transform.getPosition().y + body.getSize().y * 1.29 + rand()%17 - 8;
        snipersVelocityMultiplayer = 100;
    }
    else if(std::abs(headPosition.x - snipersRedDot->m_local_transform.getPosition().x) + std::abs(headPosition.y - snipersRedDot->m_local_transform.getPosition().y) < 1)
    {
        headPosition.x = m_local_transform.getPosition().x + body.getSize().x * 1.5 + rand()%17 - 8;
        headPosition.y = m_local_transform.getPosition().y + body.getSize().y * 1.29 + rand()%17 - 8;
    }

    snipersRedDot->velocity.x = snipersVelocityMultiplayer * (headPosition.x - snipersRedDot->m_local_transform.getPosition().x);
    snipersRedDot->velocity.y = snipersVelocityMultiplayer * (headPosition.y - snipersRedDot->m_local_transform.getPosition().y);
}

Player::Player(SoundSystem& soundSystem,sf::Vector2f position, sf::Vector2f size, float _speed, float _punchTime, float _dyingTime) : 
Character(soundSystem, position, size, _speed), punchTime(_punchTime), dyingTime(_dyingTime)
{
    snipersRedDot = std::make_shared<MovingCircle>(MovingCircle(position, 3));
    snipersRedDot->setName("snipers red dot");
    currentTime = 0.0f;
    snipersRedDot->circle.setFillColor(sf::Color::Red);
    addChild(snipersRedDot);
    snipersRedDot->translate(m_local_transform.getPosition() + sf::Vector2f(body.getSize().x / 2, body.getSize().y / 2 - 10 ));

    headPosition.x = m_local_transform.getPosition().x + body.getSize().x * 1.4 + rand()%17 - 8;
    headPosition.y = m_local_transform.getPosition().y + body.getSize().y * 1.4 + rand()%17 - 8;
}

void Player::onDraw(sf::RenderTarget &target) const
{
    target.draw(body,m_global_transform.getTransform());
}