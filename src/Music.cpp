#include"Music.hpp"
#include<iostream>

Music::Music(){
    music.setLoop(true);
    setVolume(50.f);
    playMusic();
};

void Music::setVolume(float _volume){
    volume = _volume;
    music.setVolume(50.f);
};
float Music::returnVolume() const{
    return volume;
};
void Music::setTrack(std::string _fileName){
    track = _fileName;
    playMusic();
};
std::string Music::returnTrack() const{
    return track;
};

void Music::stopMusic(){
    music.stop();
};
void Music::playMusic(){
    if(!music.openFromFile("./res/music/"+track)){
        std::cerr << "Couldn't load music!";
    }
    music.play();
};
void Music::setRepeat(bool _repeat){
    repeat = _repeat;
    music.setLoop(repeat);
};

