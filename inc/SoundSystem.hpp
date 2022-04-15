#pragma once
#include<SFML/Audio.hpp>
#include<map>
#include<deque>
#include<string>

class SoundSystem{
public:
    static SoundSystem* getInstance();
    void update();

    void playSound(std::string _fileName);
    void playSound(std::string _fileName, sf::Vector2f _position); // Spacial sounds require mono audio files. Also sf::Listener::setPosition() has to be set to the players position.

    void setVolume(float _volume);
    float returnVolume() const;
    
private:
    SoundSystem();
    static SoundSystem* instance;
    float volume = 50.f;
    std::deque<sf::Sound> soundQueque;
    std::map<std::string,sf::SoundBuffer> soundBuffer;
};