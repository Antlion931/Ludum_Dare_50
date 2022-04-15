#pragma once
#include<SFML/Audio.hpp>
#include<string>

class MusicSystem{
public:
    static MusicSystem* getInstance();

    void setVolume(float _volume);
    float returnVolume() const;

    void setTrack(std::string _fileName);
    std::string returnTrack() const;
    void setRepeat(bool _repeat);

    void stopMusic();
    void playMusic();

private:
    MusicSystem();
    static MusicSystem* instance;

    sf::Music music;
    float volume = 50.f;
    bool repeat = true;
    std::string track = "GamePlayMusic.wav";
};