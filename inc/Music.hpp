#pragma once
#include<SFML/Audio.hpp>
#include<string>

class Music{
    public:
        Music();
        void setVolume(float _volume);
        float returnVolume() const;
        void setTrack(std::string _fileName);
        std::string returnTrack() const;
        void stopMusic();
        void setRepeat(bool _repeat);
        void playMusic();
    private:
        sf::Music music;
        float volume = 50.f;
        bool repeat = true;
        std::string track = "GamePlayMusic.wav";
};