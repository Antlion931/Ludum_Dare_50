#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "stuff.hpp"
#include "Progressbar.hpp"
#include "MouseChangeableProgressbar.hpp"
#include "Resolution.hpp"

int main()
{
    Resolution resolution(Resolution::resolution::_1280x720);
    sf::RenderWindow window(resolution.getDefault(), "GAME", sf::Style::Close | sf::Style::Titlebar);

    std::vector<stuff*> stuffs;

    MouseChangeableProgressbar testBar(800.0f, 20.0f, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    testBar.setPosition(30.0f, 60.0f);

    stuffs.push_back(&testBar);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                break;
            }
        }

        window.clear();

        for(stuff* s : stuffs)
        {
            s -> draw(window);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            testBar.resize(resolution);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            testBar.resize(resolution);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            testBar.resize(resolution);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            testBar.resize(resolution);
        }
        testBar.update(window);
        
        window.display();
    }
}
