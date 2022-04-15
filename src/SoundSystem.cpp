#include"SoundSystem.hpp"
#include<iostream>
#include<filesystem>

SoundSystem* SoundSystem::instance = nullptr;

SoundSystem::SoundSystem(){
    for(const auto &entry: std::filesystem::directory_iterator("./res/sounds/")){
        sf::SoundBuffer sb;
        if(!sb.loadFromFile(entry.path().string())){
            std::cerr<<"Error while loading audio!"<<std::endl;
            continue;
        };
        std::string str = entry.path().string();
        str.erase(0,13);
        soundBuffer.insert({str,sb});
    }
}

void SoundSystem::playSound(std::string _fileName){
    soundQueque.push_back(sf::Sound(soundBuffer.at(_fileName)));
    soundQueque.back().setVolume(volume);
    soundQueque.back().play();
}

void SoundSystem::playSound(std::string _fileName, sf::Vector2f _position){
    soundQueque.push_back(sf::Sound(soundBuffer.at(_fileName)));
    sf::Sound &ref = soundQueque.back();
    ref.setRelativeToListener(true);
    ref.setPosition(_position.x,0.f,_position.y);   //TOTWEAK
    ref.setMinDistance(50.f);   //TOTWEAK
    ref.setAttenuation(1.f);    //TOTWEAK
    ref.play();
}

void SoundSystem::update(){
    for(int i=0; i<soundQueque.size(); i++)
        if(soundQueque.at(i).getStatus() == sf::Sound::Stopped){
            soundQueque.erase(soundQueque.begin()+i--);
        }
}

void SoundSystem::setVolume(float _volume){
    volume = _volume;
}

float SoundSystem::returnVolume() const{
    return volume;
}

SoundSystem* SoundSystem::getInstance()
{
    if(instance == nullptr)
    {
        instance = new SoundSystem();
    }

    return instance;
}
