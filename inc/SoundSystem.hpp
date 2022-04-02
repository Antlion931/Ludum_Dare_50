#pragma once
#include<SFML/Audio.hpp>
#include<map>
#include<deque>
#include<string>

class SoundSystem{
    public:
        SoundSystem();
        void playSound(std::string _fileName);
        void playSound(std::string _fileName, sf::Vector2f _position); // Spacial sounds require mono audio files. Also sf::Listener::setPosition() has to be set to the players position.
        void update();
        void setVolume(float _volume);
        float returnVolume() const;
    private:
        float volume = 50.f;
        std::deque<sf::Sound> soundQueque;
        std::map<std::string,sf::SoundBuffer> soundBuffer;
};