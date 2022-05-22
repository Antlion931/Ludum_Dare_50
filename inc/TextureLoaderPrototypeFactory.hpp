#pragma once
#include "TextureLoader.hpp"

class TextureLoaderPrototypeFactory
{
public:
    std::shared_ptr<TextureLoader> make(std::string name);
    static TextureLoaderPrototypeFactory* getInstance(std::string directoryPath = "");

private:
    TextureLoaderPrototypeFactory(std::string directoryPath);
    std::map<std::string, TextureLoader> prototypes;

    static TextureLoaderPrototypeFactory* instance;
};
