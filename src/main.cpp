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
#include "Player.hpp"
#include "Music.hpp"
#include "SoundSystem.hpp"
#include "Animation.hpp"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "Y-sort.hpp"
#include "Chunk.hpp"
#include "Y-sort.hpp"
#include "CameraController.hpp"
#include "Root.hpp"
#include "WorldView.hpp"

enum
{
MAIN_MENU,
TEST_PLAY,
SETTINGS,
GAME
};

int main()
{
    std::srand(std::time(NULL));
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

    std::unique_ptr<Root> root = std::make_unique<Root>(Root());

    std::shared_ptr<LevelLoader> game = std::make_shared<LevelLoader>(LevelLoader(4));
    game->setName("game");
    root->setGame(game);

    std::shared_ptr<LevelLoader> GUI = std::make_shared<LevelLoader>(LevelLoader(4));
    GUI->setName("gui");
    root->setGUI(GUI);

    SoundSystem GLOBAL_SOUND_SYSTEM;

    std::shared_ptr<YSort> ysort = std::make_shared<YSort>(YSort());

    //================================================================================================MAIN MENU
    std::shared_ptr<Node> mainMenu = std::make_shared<Node>(Node());
    mainMenu->setName("Main Menu");
    GUI->addLevel(MAIN_MENU, mainMenu);
    game->setLevel(MAIN_MENU);
    GUI->setLevel(MAIN_MENU);

    std::shared_ptr<Container> mainMenuButtons = std::make_shared<Container>();
    mainMenuButtons->setName("Main Menu Buttons");
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
    TextureLoader tileSets("./res/textures/TileSets");

    std::shared_ptr<Node> test = std::make_shared<Node>(Node());
    std::shared_ptr<Container> test_menu = std::make_shared<Container>(Container());
    test->setName("Test");
    
    game->addLevel(TEST_PLAY, test);
    GUI->addLevel(TEST_PLAY, test_menu);


    std::shared_ptr<CollisionLayer> test_layer = std::make_shared<CollisionLayer>(CollisionLayer());
    std::shared_ptr<Container> test_container = std::make_shared<Container>(Container());


    std::shared_ptr<NPC> testNPC1 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {400,400}, {100,100}, 100, 1));
    testNPC1->setName("test NPC1");
    testNPC1->setCollider(test_layer, {0.0, 25.0}, 30.0);
    test_container->addChild(testNPC1);
    testNPC1->setRunAnimation("./res/textures/npc/Female/Run", 0.1);
    testNPC1->setIdleAnimation("./res/textures/npc/Female/Idle", 0.2);
    testNPC1->setDyingAnimation("./res/textures/npc/Female/Dying", 1);
    testNPC1->setDeadAnimation("./res/textures/npc/Female/Dead", 1);
    testNPC1->setDyingSoundName("dead.wav");
    ysort->addChild(testNPC1);

    std::shared_ptr<NPC> testNPC2 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {500,400}, {100,100}, 100, 1));
    testNPC2->setName("test NPC");
    testNPC2->setCollider(test_layer, {0.0, 25.0}, 30.0);
    test_container->addChild(testNPC2);
    testNPC2->setRunAnimation("./res/textures/npc/Male/Run", 0.1);
    testNPC2->setIdleAnimation("./res/textures/npc/Male/Idle", 0.2);
    testNPC2->setDyingAnimation("./res/textures/npc/Male/Dying", 1);
    testNPC2->setDeadAnimation("./res/textures/npc/Male/Dead", 1);
    testNPC2->setDyingSoundName("dead.wav");
    ysort->addChild(testNPC2);

    std::shared_ptr<NPC> testNPC3 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {600,400}, {100,100}, 100, 1));
    testNPC3->setName("test NPC");
    testNPC3->setCollider(test_layer, {0.0, 25.0}, 30.0);
    test_container->addChild(testNPC3);
    testNPC3->setRunAnimation("./res/textures/npc/Butcher/Run", 0.1);
    testNPC3->setIdleAnimation("./res/textures/npc/Butcher/Idle", 0.2);
    testNPC3->setDyingAnimation("./res/textures/npc/Butcher/Dying", 1);
    testNPC3->setDeadAnimation("./res/textures/npc/Butcher/Dead", 1);
    testNPC3->setDyingSoundName("dead.wav");
    ysort->addChild(testNPC3);

    std::shared_ptr<NPC> testNPC4 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {700,400}, {100,100}, 100, 1));
    testNPC4->setName("test NPC4");
    testNPC4->setCollider(test_layer, {0.0, 25.0}, 30.0);
    test_container->addChild(testNPC4);
    testNPC4->setRunAnimation("./res/textures/npc/Herald/Run", 0.1);
    testNPC4->setIdleAnimation("./res/textures/npc/Herald/Idle", 0.2);
    testNPC4->setDyingAnimation("./res/textures/npc/Herald/Dying", 1);
    testNPC4->setDeadAnimation("./res/textures/npc/Herald/Dead", 1);
    testNPC4->setDyingSoundName("dead.wav");
    ysort->addChild(testNPC4);

    std::shared_ptr<Player> player = std::make_shared<Player>(Player(GLOBAL_SOUND_SYSTEM, {100,100}, {100, 100}, 600, 0.55, 0.4));
    player->setName("Player");
    player->setCollider(test_layer, {0.0, 0.0}, 40.0);
    ysort->addChild(player);

    std::shared_ptr<WorldView> worldView = std::make_shared<WorldView>(WorldView(player, tileSets.returnTexture("outdoors.png")));
    worldView->setName("World View");
    test->addChild(worldView);

    std::shared_ptr<CameraController> cameraController = std::make_shared<CameraController>(CameraController(player));
    player->addChild(cameraController);

    std::shared_ptr<Collidable> obstacle_1 = std::make_shared<Collidable>(Collidable());
    obstacle_1->setCollider(test_layer, {0, 0}, 50.0);
    obstacle_1->setTranslation({500, 500});
    ysort->addChild(obstacle_1);

    std::shared_ptr<Collidable> obstacle_2 = std::make_shared<Collidable>(Collidable());
    obstacle_2->setCollider(test_layer, {0, 0}, 50.0);
    obstacle_2->setTranslation({550, 500});
    ysort->addChild(obstacle_2);

    std::shared_ptr<Collidable> obstacle_3 = std::make_shared<Collidable>(Collidable());
    obstacle_3->setCollider(test_layer, {0, 0}, {100.0, 50.0});
    obstacle_3->setTranslation({700, 500});
    obstacle_3->scale({2.0,2.0});
    ysort->addChild(obstacle_3);

    test->addChild(test_container);
    test_container->addChild(ysort);

    test_container->addChild(player);
    player->setIdleAnimation("./res/textures/Player/1-Idle", 0.06);
    player->setRunAnimation("./res/textures/Player/2-Run", 0.03);
    player->setPunchAnimation("./res/textures/Player/7-Attack", 0.05);
    player->setDyingAnimation("./res/textures/Player/12-Hit", 0.05);
    player->setDeadAnimation("./res/textures/Player/14-DeadGround", 0.1);
    player->setDyingSoundName("gunShot.wav");

    ComisBookText.setString("KILL");
    ComisBookText.setCharacterSize(90);
    std::shared_ptr<ColoredButton> killButton = std::make_shared<ColoredButton>(ColoredButton({ 800,50 }, { 300,100 }, ComisBookText));
    killButton->setName("kill button");
    killButton->setOnNotHoveredButtonStyle(Style(sf::Color(200, 200, 200), sf::Color(180, 180, 180), 10));
    killButton->setOnEntredButtonStyle(Style(sf::Color(210, 210, 210), sf::Color(190, 190, 190), 20));
    killButton->setOnPressedButtonStyle(Style(sf::Color(190, 190, 190), sf::Color(170, 170, 170), 5));
    killButton->setOnEnteredFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    killButton->setOnPressedFontStyle(Style(sf::Color::Yellow, sf::Color::Black, 4));
    test_menu->addChild(killButton);

    test->setName("Test");
 
    //===================================================================================================SETTINGS

    std::shared_ptr<Node> settings = std::make_shared<Node>(Node());
    settings -> setName("Settings");
    GUI->addLevel(SETTINGS, settings);

    std::shared_ptr<Container> resolutionSettings = std::make_shared<Container>();
    resolutionSettings->setName("Resolution Settings");
    settings->addChild(resolutionSettings);

    ComisBookText.setCharacterSize(20);
        
    ComisBookText.setString("_1280 x 720");
    std::shared_ptr<ColoredButton> _1280x720button = std::make_shared<ColoredButton>(ColoredButton({ 150,200 }, { 200,100 }, ComisBookText));
    _1280x720button->setName("_1280x720button");
    resolutionSettings->addChild(_1280x720button);

    ComisBookText.setString("1336 x 768");
    std::shared_ptr<ColoredButton> _1336x768button = std::make_shared<ColoredButton>(ColoredButton({ 400,200 }, { 200,100 }, ComisBookText));
    _1336x768button->setName("_1336x768button");
    resolutionSettings->addChild(_1336x768button);

    ComisBookText.setString("1600 x 900");
    std::shared_ptr<ColoredButton> _1600x900button = std::make_shared<ColoredButton>(ColoredButton({ 650,200 }, { 200,100 }, ComisBookText));
    _1600x900button->setName("_1600x900button");
    resolutionSettings->addChild(_1600x900button);

    ComisBookText.setString("1900 x 1080");
    std::shared_ptr<ColoredButton> _1900x1080button = std::make_shared<ColoredButton>(ColoredButton({ 900,200 }, { 200,100 }, ComisBookText));
    _1900x1080button->setName("_1900x1080button");
    resolutionSettings->addChild(_1900x1080button);

    ComisBookText.setString("GO BACK");
    std::shared_ptr<ColoredButton> goBackButton = std::make_shared<ColoredButton>(ColoredButton({ 525,500 }, { 200,100 }, ComisBookText));
    _1900x1080button->setName("Go Back Button");
    resolutionSettings->addChild(goBackButton);

    
    //========================================================================================GAME
    std::shared_ptr<Node> game_level = std::make_shared<Node>(Node());
    game->addLevel(GAME, game_level);

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
                    root->setLevel(MAIN_MENU);
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    root->setLevel(SETTINGS);
                }
                else if (event.key.code == sf::Keyboard::Num3)
                {
                    std::cout << "button _1920x1080 is: " << (_1900x1080button->isActive() ? "active\n" : "inactive\n");
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    root->printTree();
                }
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
            _1336x768button->printDebug();
        }

        if (_1600x900button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root->resize(resolution);
            _1600x900button->printDebug();
        }

        if (_1900x1080button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            root->resize(resolution);
            _1900x1080button->printDebug();
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

        if(killButton->isPressed(window))
        {
            player->kill();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
        {
            testNPC1->kill();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
        {
            testNPC2->kill();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
        {
            testNPC3->kill();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
        {
            testNPC4->kill();
        }

        GLOBAL_SOUND_SYSTEM.update();

        sf::Time delta = deltaClock.restart();
        window.clear();

        root->update(delta);
        //std::cout << "Delta: " << delta.asMilliseconds() << "\n";

        sf::View new_view = window.getView();
        new_view.setCenter(cameraController->getRequiredTranslation());
        window.setView(new_view);
        GUI->setTranslation(cameraController->getRequiredTranslation() - new_view.getSize() / 2.0f);

        root->draw(window);

        window.display();
    }
}