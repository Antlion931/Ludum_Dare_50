#pragma once
#include <vector>

#include "GameObject.hpp"
#include "QuestCreator.hpp"
#include "DialogueBox.hpp"

class NPC : public GameObject
{
private:
    float walkTime;
    float waitTime;
    bool talkable = true;

    void onUpdate(const sf::Time &delta) override;
    void randomVelocityAndTimes();
    std::shared_ptr<DialogueBox> db = nullptr;
    inline static std::shared_ptr<QuestCreator> qC;
public:
    inline static sf::Font font;
    NPC(sf::Vector2f position, sf::Vector2f size, float _speed, AnimationManager _animationManager, float _dyingTime);

    inline static void setQuestCreator(std::shared_ptr<QuestCreator> _qC){qC = _qC;};
};