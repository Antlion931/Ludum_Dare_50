#include"Quest.hpp"

Quest::Quest(QuestType _questType,int _remainingMiliseconds){
    questType = _questType;
    timeElapsedFromQuestStart.restart();
    timeForQuest = sf::milliseconds(_remainingMiliseconds);
};

void Quest::setQuestAsDone(){
    Done = true;
};
bool Quest::isDone() const{
    return Done;
};
sf::Time Quest::returnRemainingTime() const{
    sf::Time returnTime = timeForQuest - timeElapsedFromQuestStart.getElapsedTime();
    return returnTime;
};
QuestType Quest::returnQuestType() const{
    return questType;
};