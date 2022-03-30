#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "stuff.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(840, 600), "GAME", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

    std::vector<stuff*> stuffs;

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
        
        window.display();
    }
}