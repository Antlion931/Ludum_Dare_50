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

    MouseChangeableProgressbar testBar(400.0f, 20.0f, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    testBar.setPosition(30.0f, 60.0f);
    testBar.resolution = &resolution;

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
        
        window.display();
    }
}
