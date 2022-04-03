#include"Quest.hpp"

Quest::Quest(Character* _questObjective,QuestType _questType,int _remainingMiliseconds){
    questObjective = _questObjective;
    questType = _questType;
    timeElapsedFromQuestStart.restart();
    timeForQuest = sf::milliseconds(_remainingMiliseconds);
};

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
    return returnTime;
};
QuestType Quest::returnQuestType() const{
    return questType;
};

Character* Quest::returnQuestObjective()const{
    return questObjective;
};
 