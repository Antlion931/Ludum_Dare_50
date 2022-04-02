#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Progressbar.hpp"
#include "MouseChangeableProgressbar.hpp"
#include "Resolution.hpp"
#include "Node.hpp"
#include "Button.hpp"
#include "TextButton.hpp"
#include "Container.hpp"
#include "LevelLoader.hpp"
#include "TextureLoader.hpp"
#include "MovingCircle.hpp"
#include "ColoredButton.hpp"
#include "Collision.hpp"

enum
{
MAIN_MENU,
TEST_PLAY,
SETTINGS,
GAME
};

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

    sf::Text ComisBookText("place holder", font);
    ComisBookText.setCharacterSize(20);

    std::unique_ptr<LevelLoader> root = std::make_unique<LevelLoader>(LevelLoader());
    root->setName("root");

    //================================================================================================MAIN MENU
    std::shared_ptr<Node> mainMenu = std::make_shared<Node>(Node());
    root->addLevel(mainMenu);

    std::shared_ptr<Container> mainMenuButtons = std::make_shared<Container>();
    mainMenuButtons->setName("Resolution Settings");
    mainMenu->addChild(mainMenuButtons);

    ComisBookText.setString("PLAY");
    ComisBookText.setCharacterSize(90);
    std::shared_ptr<ColoredButton> playButton = std::make_shared<ColoredButton>(ColoredButton({ 490,50 }, { 300,100 }, ComisBookText));
    playButton->setName("Play button");
    playButton->setOnNotHoveredButtonStyle(Style(sf::Color(200, 200, 200), sf::Color(180, 180, 180), 10));
    playButton->setOnEntredButtonStyle(Style(sf::Color(210, 210, 210), sf::Color(190, 190, 190), 20));
    playButton->setOnPressedButtonStyle(Style(sf::Color(190, 190, 190), sf::Color(170, 170, 170), 5));
    playButton->setOnEnteredFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    playButton->setOnPressedFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    mainMenuButtons->addChild(playButton);

    ComisBookText.setString("SETTINGS");
    ComisBookText.setCharacterSize(55);
    std::shared_ptr<ColoredButton> settingsButton = std::make_shared<ColoredButton>(ColoredButton({ 490,250 }, { 300,100 }, ComisBookText));
    settingsButton->setName("settings button");
    settingsButton->setOnNotHoveredButtonStyle(Style(sf::Color(200, 200, 200), sf::Color(180, 180, 180), 20));
    settingsButton->setOnEntredButtonStyle(Style(sf::Color(210, 210, 210), sf::Color(190, 190, 190), 30));
    settingsButton->setOnPressedButtonStyle(Style(sf::Color(190, 190, 190), sf::Color(170, 170, 170), 10));
    settingsButton->setOnEnteredFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    settingsButton->setOnPressedFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    mainMenuButtons->addChild(settingsButton);

    ComisBookText.setString("TEST");
    ComisBookText.setCharacterSize(90);
    std::shared_ptr<ColoredButton> testButton = std::make_shared<ColoredButton>(ColoredButton({ 490,450 }, { 300,100 }, ComisBookText));
    testButton->setName("Test button");
    testButton->setOnNotHoveredButtonStyle(Style(sf::Color(200, 200, 200), sf::Color(180, 180, 180), 10));
    testButton->setOnEntredButtonStyle(Style(sf::Color(210, 210, 210), sf::Color(190, 190, 190), 20));
    testButton->setOnPressedButtonStyle(Style(sf::Color(190, 190, 190), sf::Color(170, 170, 170), 5));
    testButton->setOnEnteredFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    testButton->setOnPressedFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    mainMenuButtons->addChild(testButton);

    //====================================================================================================TESTING
    std::shared_ptr<Node> test = std::make_shared<Node>(Node());
    root->addLevel(test);

    std::shared_ptr<CollisionLayer> test_layer = std::make_shared<CollisionLayer>(CollisionLayer()); 

    std::shared_ptr<Collidable> kolizja_test_1 = std::make_shared<Collidable>(Collidable());
    kolizja_test_1->setCollider(test_layer, {0,0}, 50.0);
    test->addChild(kolizja_test_1);

    std::shared_ptr<Collidable> kolizja_test_2 = std::make_shared<Collidable>(Collidable());
    kolizja_test_2->translate({10.0, 10.0});
    kolizja_test_2->setCollider(test_layer, {0,0}, 50.0);
    test->addChild(kolizja_test_2);
    //===================================================================================================SETTINGS

    std::shared_ptr<Node> settings = std::make_shared<Node>(Node());
    root->addLevel(settings);

    std::shared_ptr<Container> resolutionSettings = std::make_shared<Container>();
    resolutionSettings->setName("Resolution Settings");
    settings->addChild(resolutionSettings);

    resolutionSettings->translate({ 100, 100 });
        
    ComisBookText.setString("_1280 x 720");
    std::shared_ptr<ColoredButton> _1280x720button = std::make_shared<ColoredButton>(ColoredButton({ 50,200 }, { 200,100 }, ComisBookText));
    _1280x720button->setName("_1280x720button");
    resolutionSettings->addChild(_1280x720button);

    ComisBookText.setString("1336 x 768");
    std::shared_ptr<ColoredButton> _1336x768button = std::make_shared<ColoredButton>(ColoredButton({ 300,200 }, { 200,100 }, ComisBookText));
    _1336x768button->setName("_1336x768button");
    resolutionSettings->addChild(_1336x768button);

    ComisBookText.setString("1600 x 900");
    std::shared_ptr<ColoredButton> _1600x900button = std::make_shared<ColoredButton>(ColoredButton({ 550,200 }, { 200,100 }, ComisBookText));
    _1600x900button->setName("_1600x900button");
    resolutionSettings->addChild(_1600x900button);

    ComisBookText.setString("1900 x 1080");
    std::shared_ptr<ColoredButton> _1900x1080button = std::make_shared<ColoredButton>(ColoredButton({ 800,200 }, { 200,100 }, ComisBookText));
    _1900x1080button->setName("_1900x1080button");
    resolutionSettings->addChild(_1900x1080button);

    ComisBookText.setString("GO BACK");
    std::shared_ptr<ColoredButton> goBackButton = std::make_shared<ColoredButton>(ColoredButton({ 1050,200 }, { 200,100 }, ComisBookText));
    _1900x1080button->setName("Go Back Button");
    resolutionSettings->addChild(goBackButton);

    
    //========================================================================================GAME
    std::shared_ptr<Node> game = std::make_shared<Node>(Node());
    root->addLevel(game);

    //=========================================================================================GAME LOOP
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Num1)
                {
                    root->setLevel(0);
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    root->setLevel(1);
                }
                else if (event.key.code == sf::Keyboard::Space)
                    kolizja_test_2->translateGlobal(kolizja_test_2->scanCollisions().move_vector);
                break;
            }
        }

        if (_1280x720button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if (_1336x768button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if (_1600x900button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if (_1900x1080button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if(playButton->isPressed(window))
        {
            root->setLevel(GAME);
        }

        if(settingsButton->isPressed(window))
        {
            root->setLevel(SETTINGS);
        }

        if(testButton->isPressed(window))
        {
            root->setLevel(TEST_PLAY);
        }

        if(goBackButton->isPressed(window))
        {
            root->setLevel(MAIN_MENU);
        }

        sf::Time delta = deltaClock.restart();
        window.clear();

        root->update(delta);
        root->draw(window);

        window.display();
    }
}