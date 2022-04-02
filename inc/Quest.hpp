#pragma once
#include<SFML/System/Clock.hpp>
enum QuestType{
    hug,talk,kill,steal
};

class Quest{
    public:
        Quest(QuestType _questType = hug,int _remainingMiliseconds = 30000);
        void setQuestAsDone();
        bool isDone() const;
        sf::Time returnRemainingTime() const;
        //Character* returnQuestObjective();
        QuestType returnQuestType() const;
    private:
        QuestType questType;
        // Character* questObjective
        bool Done = false;
        sf::Time timeForQuest;
        sf::Clock timeElapsedFromQuestStart;
};