#pragma once
#include<SFML/System/Clock.hpp>
#include"Character.hpp"
enum QuestType{
    hug,talk,kill,steal
};

class Quest{
    public:
        static std::string questTypeToString(QuestType type);
        Quest(Character* _questObjective,QuestType _questType = hug,int _remainingMiliseconds = 30000);
        Quest(std::string _questObjectiveType,QuestType _questType = hug,int _remainingMiliseconds = 30000);
        void setQuestAsDone();
        void setQuestAsFailed();
        bool isDone() const;
        sf::Time returnRemainingTime() const;
        Character* returnQuestObjective() const;
        std::string returnQuestObjectiveType() const;
        QuestType returnQuestType() const;
        bool Done = false;
        bool Failed = false;
    private:
        std::string questObjectiveType;
        QuestType questType;
        Character* questObjective;
        sf::Time timeForQuest;
        sf::Clock timeElapsedFromQuestStart;
};