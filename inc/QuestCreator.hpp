#pragma once
#include"Quest.hpp"
#include"Player.hpp"

class QuestCreator{

    public:
        enum PulseType{
            KILL, TALK, HUG, CLEAR
        };
        struct Pulse{
            PulseType pulseType;
            std::string pulseEmitter;
        };

        QuestCreator(std::shared_ptr<Player> _player);
        void addQuest(Quest _quest);
        void update();  // Sprawdza czy quest został wykponany/przegrany itp.
        std::vector<Quest> activeQuests;
        std::vector<Quest> failedQuests;
        std::vector<Quest> completedQuests;

        void sendPulse(PulseType _pulse, std::string _name);
    private:
        std::shared_ptr<Player> player;
        Pulse lastPulse = {CLEAR,""};

};