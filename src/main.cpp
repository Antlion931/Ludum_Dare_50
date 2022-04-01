#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Progressbar.hpp"
#include "MouseChangeableProgressbar.hpp"
#include "Resolution.hpp"
#include "Node.hpp"
#include "Button.hpp"
#include "TextButton.hpp"
<<<<<<< HEAD
=======
#include "Container.hpp"
>>>>>>> 86446ff06695ba1d4ca7b86f825c3189c3434de6

int main()
{
    Resolution resolution(Resolution::resolution::_1280x720);
    sf::RenderWindow window(resolution.getDefault(), "GAME", sf::Style::Close | sf::Style::Titlebar);

    sf::Font font;

<<<<<<< HEAD
    sf::Text text("przycisk", font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(50);
    
    if (!font.loadFromFile("rsc/Comic_Book.otf"))
=======
    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }
    
    sf::Text buttonText("place holder", font);
    buttonText.setFillColor(sf::Color::Red);
    buttonText.setCharacterSize(20);

    Node* root = new Node();
    root->setName("root");
    
    buttonText.setString("1280 x 720");
    std::shared_ptr<TextButton> _1280x720button = std::make_shared<TextButton>(TextButton({ 50,200 }, { 200,100 }, buttonText));
    _1280x720button->setName("_1280x720button");

    buttonText.setString("1336 x 768");
    std::shared_ptr<TextButton> _1336x768button = std::make_shared<TextButton>(TextButton({ 300,200 }, { 200,100 }, buttonText));
    _1336x768button->setName("_1336x768button");

    buttonText.setString("1600 x 900");
    std::shared_ptr<TextButton> _1600x900button = std::make_shared<TextButton>(TextButton({ 550,200 }, { 200,100 }, buttonText));
    _1600x900button->setName("_1600x900button");

    buttonText.setString("1900 x 1080");
    std::shared_ptr<TextButton> _1900x1080button = std::make_shared<TextButton>(TextButton({ 800,200 }, { 200,100 }, buttonText));
    _1900x1080button->setName("_1900x1080button");

    std::shared_ptr<MouseChangeableProgressbar> progressbar = std::make_shared<MouseChangeableProgressbar>(1000.0f, 50.0f, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    progressbar->setName("progressbar");

    std::shared_ptr<Container> container = std::make_shared<Container>();
    container->setName("container");

    container->addChild(_1280x720button);
    container->addChild(_1336x768button);
    container->addChild(_1600x900button);
    container->addChild(_1900x1080button);
    root->addChild(progressbar);
    root->addChild(container);

    container -> translate({100, 100});
    progressbar -> translate({100, 100});

    sf::Text text("przycisk", font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(50);

    root->printTree();
    
    if (!font.loadFromFile("res/Comic_Book.otf"))
>>>>>>> 86446ff06695ba1d4ca7b86f825c3189c3434de6
    {
        std::cerr << "font errore!\n";
        return 0;
    }
<<<<<<< HEAD


    Node root;
    std::shared_ptr<Node> player = std::make_shared<Node>(Node()); 
    std::shared_ptr<TextButton> button = std::make_shared<TextButton>(TextButton({ 100,100 }, { 300,200 }, text));
    root.addChild(player);
    player->addChild(button);
    
=======
>>>>>>> 86446ff06695ba1d4ca7b86f825c3189c3434de6
 
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

<<<<<<< HEAD
                case sf::Event::Resized:
                {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                }
                break;

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        //player->move({0.0,10.0});
                        player->move({10.0,0.0});
                    }

                    if (event.key.code == sf::Keyboard::Up)
                    {
                        player->rotate(30.0);
                    }

                    if (event.key.code == sf::Keyboard::Down)
                    {
                        player->scale({2.0,0.5});
                    }
                }
            }
=======

        progressbar->update(window);

        if(_1280x720button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            root->resize(resolution);
            _1280x720button->printDebug();
>>>>>>> 86446ff06695ba1d4ca7b86f825c3189c3434de6
        }

        if(_1336x768button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if(_1600x900button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if(_1900x1080button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        window.clear();

        root->draw(window);
        
        window.display();
    }
}
