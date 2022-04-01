#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Progressbar.hpp"
#include "MouseChangeableProgressbar.hpp"
#include "Resolution.hpp"
#include "Node.hpp"
#include "Button.hpp"
#include "TextButton.hpp"

int main()
{
    Resolution resolution(Resolution::resolution::_1280x720);
    sf::RenderWindow window(resolution.getDefault(), "GAME", sf::Style::Close | sf::Style::Titlebar);

    sf::Font font;

    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }
    
    sf::Text buttonText("place holder", font);
    buttonText.setFillColor(sf::Color::Red);
    buttonText.setCharacterSize(20);

    Node root;
    
    buttonText.setString("1280 x 720");
    std::shared_ptr<TextButton> _1280x720button = std::make_shared<TextButton>(TextButton({ 50,200 }, { 200,100 }, buttonText));

    buttonText.setString("1336 x 768");
    std::shared_ptr<TextButton> _1336x768button = std::make_shared<TextButton>(TextButton({ 300,200 }, { 200,100 }, buttonText));

    buttonText.setString("1600 x 900");
    std::shared_ptr<TextButton> _1600x900button = std::make_shared<TextButton>(TextButton({ 550,200 }, { 200,100 }, buttonText));

    buttonText.setString("1900 x 1080");
    std::shared_ptr<TextButton> _1900x1080button = std::make_shared<TextButton>(TextButton({ 800,200 }, { 200,100 }, buttonText));

    std::shared_ptr<MouseChangeableProgressbar> progressbar = std::make_shared<MouseChangeableProgressbar>(1000.0f, 50.0f, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    root.addChild(_1280x720button);
    root.addChild(_1336x768button);
    root.addChild(_1600x900button);
    root.addChild(_1900x1080button);
    root.addChild(progressbar);

    progressbar -> move({100, 100});

    sf::Text text("przycisk", font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(50);
    
    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }
 
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


        progressbar->update(window);

        if(_1280x720button->isPressed(window))
        {
            std::cout << "a\n";
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            root.resize(resolution);
        }

        if(_1336x768button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            root.resize(resolution);
        }

        if(_1600x900button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root.resize(resolution);
        }

        if(_1900x1080button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            root.resize(resolution);
        }

        window.clear();

        root.draw(window);
        
        window.display();
    }
}
