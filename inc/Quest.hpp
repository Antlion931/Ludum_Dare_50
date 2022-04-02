#pragma once
#include<SFML/System/Clock.hpp>
#include"Character.hpp"
enum QuestType{
    hug,talk,kill,steal
};

class Quest{
    public:
        Quest(Character* _questObjective,QuestType _questType = hug,int _remainingMiliseconds = 30000);
        void setQuestAsDone();
        void setQuestAsFailed();
        bool isDone() const;
        sf::Time returnRemainingTime() const;
        Character* returnQuestObjective() const;
        QuestType returnQuestType() const;
    private:
        QuestType questType;
        Character* questObjective;
        bool Done = false;
        bool Failed = false;
        sf::Time timeForQuest;
        sf::Clock timeElapsedFromQuestStart;
};