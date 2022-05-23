#include"Quest.hpp"

Quest::Quest(GameObject* _questObjective,QuestType _questType,int _remainingMiliseconds){
    questObjectiveType = _questObjective->getName();
    questObjective = _questObjective;
    questType = _questType;
    timeElapsedFromQuestStart.restart();
    timeForQuest = sf::milliseconds(_remainingMiliseconds);
};
Quest::Quest(std::string _questObjectiveType,QuestType _questType,int _remainingMiliseconds){
    questObjectiveType = _questObjectiveType;
    questObjective = nullptr;
    questType = _questType;
    timeElapsedFromQuestStart.restart();
    timeForQuest = sf::milliseconds(_remainingMiliseconds);
};

std::string Quest::questTypeToString(QuestType type)
{
    switch (type) 
    {
        case hug:
            return "HUG";
        case talk:
            return "TALK";
        case kill:
            return "KILL";
        case steal:
            return "STEAL";
    }
}

void Quest::setQuestAsDone(){
    /*
        Coś się dzieje?
    */
    Done = true;
};
void Quest::setQuestAsFailed(){
    /*
        Też coś się dzieje?
    */
    Failed = true;
};
bool Quest::isDone() const{
    std::cout << "Quest Done!" << std::endl;
    return Done;
};
sf::Time Quest::returnRemainingTime() const{
    sf::Time returnTime = timeForQuest - timeElapsedFromQuestStart.getElapsedTime();
    return returnTime; //returnTime;
};
QuestType Quest::returnQuestType() const{
    return questType;
};

GameObject* Quest::returnQuestObjective()const{
    return questObjective;
};
std::string Quest::returnQuestObjectiveType() const{
    return questObjectiveType;
};
 