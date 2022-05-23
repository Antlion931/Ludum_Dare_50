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
    float speed;
    bool talkable = true;
    sf::Vector2f velocity;

    void onUpdate(const sf::Time &delta) override;
    void randomVelocityAndTimes();
    std::shared_ptr<DialogueBox> db = nullptr;
    inline static std::shared_ptr<QuestCreator> qC;

    double currentTime;

public:
    inline static sf::Font font;
    NPC(sf::Vector2f position, std::string animationDirectoryName, float idleTime, float dyingTime, float deadTime, float runTime, float _speed);

    inline static void setQuestCreator(std::shared_ptr<QuestCreator> _qC){qC = _qC;};
};