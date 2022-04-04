#pragma once
#include <vector>

#include "Character.hpp"
#include "QuestCreator.hpp"
#include "DialogueBox.hpp"

class NPC : public Character
{
private:
    float walkTime;
    float waitTime;
    bool talkable = true;
    bool dead = false;

    void onUpdate(const sf::Time &delta) override;
    void randomVelocityAndTimes();
    sf::Font font;
    std::shared_ptr<DialogueBox> db = nullptr;
    inline static std::shared_ptr<QuestCreator> qC;
public:

    


    NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, Animation, float _dyingTime);
    void setUpByName(std::string name);

    inline static void setQuestCreator(std::shared_ptr<QuestCreator> _qC){qC = _qC;};
};