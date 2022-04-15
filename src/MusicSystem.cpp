#include"MusicSystem.hpp"
#include<iostream>

MusicSystem* MusicSystem::instance = nullptr;

MusicSystem::MusicSystem(){
    music.setLoop(true);
    setVolume(50.f);
    playMusic();
}

void MusicSystem::setVolume(float _volume){
    volume = _volume;
    music.setVolume(volume);
}

void MusicSystem::playMusic(){
    if(!music.openFromFile("./res/music/"+track)){
        std::cerr << "Couldn't load music!";
    }
    music.play();
}

float MusicSystem::returnVolume() const{
    return volume;
}

void MusicSystem::setTrack(std::string _fileName){
    track = _fileName;
    playMusic();
}

std::string MusicSystem::returnTrack() const{
    return track;
}

void MusicSystem::stopMusic(){
    music.stop();
}

void MusicSystem::setRepeat(bool _repeat){
    repeat = _repeat;
    music.setLoop(repeat);
}

MusicSystem* MusicSystem::getInstance()
{
    if(instance == nullptr)
    {
        instance = new MusicSystem();
    }

    return instance;
}
