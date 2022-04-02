#pragma once
#include<SFML/Audio.hpp>
#include<map>
#include<deque>
#include<string>

class SoundSystem{
    public:
        SoundSystem();
        void playSound(std::string _fileName);
        void update();
        void setVolume(float _volume);
        float returnVolume() const;
    private:
        float volume = 50.f;
        std::deque<sf::Sound> soundQueque;
        std::map<std::string,sf::SoundBuffer> soundBuffer;
};