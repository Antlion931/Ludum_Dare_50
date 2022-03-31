#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Node.hpp"
#include "Button.h"
#include "TextButton.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(840, 600), "GAME", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

    sf::Font font;

    sf::Text text("przycisk", font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(50);
    
    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }


    Node root;
    std::shared_ptr<TextButton> button = std::make_shared<TextButton>(TextButton({ 100,100 }, { 300,200 }, text));
    root.addChild(button);

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
                }
                break;
            }
        }

        button->isPressed(window);

        window.clear();

        root.draw(window);
        
        window.display();
    }
}
