#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "stuff.hpp"
#include "Progressbar.hpp"
#include "MouseChangeableProgressbar.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(840, 600), "GAME", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

    std::vector<stuff*> stuffs;

    MouseChangeableProgressbar testBar(400.0f, 20.0f, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
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

                case sf::Event::Resized:
                {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));

                    for(stuff* s : stuffs)
                    {
                        s -> resize(window);
                    }
                }
                break;
            }
        }

        window.clear();

        for(stuff* s : stuffs)
        {
            s -> draw(window);
        }

        testBar.update(window);
        
        window.display();
    }
}
