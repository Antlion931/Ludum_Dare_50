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
#include "Chunk.hpp"
#include "Y-sort.hpp"
#include "CameraController.hpp"
#include "Root.hpp"
#include "ButtonsContainer.hpp"

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

    std::unique_ptr<Root> root = std::make_unique<Root>(Root());

    std::shared_ptr<LevelLoader> game = std::make_shared<LevelLoader>(LevelLoader(4));
    game->setName("game");
    root->setGame(game);

    std::shared_ptr<LevelLoader> GUI = std::make_shared<LevelLoader>(LevelLoader(4));
    GUI->setName("gui");
    root->setGUI(GUI);

    SoundSystem GLOBAL_SOUND_SYSTEM;

    //================================================================================================MAIN MENU
    std::shared_ptr<Node> mainMenu = std::make_shared<Node>(Node());
    mainMenu->setName("Main Menu");
    GUI->addLevel(MAIN_MENU, mainMenu);
    game->setLevel(MAIN_MENU);
    GUI->setLevel(MAIN_MENU);

    std::shared_ptr<ButtonsContainer> mainMenuButtons = std::make_shared<ButtonsContainer>(ButtonsContainer(font));
    mainMenuButtons->setName("Main Menu Buttons");
    mainMenu->addChild(mainMenuButtons);

    mainMenuButtons->makeColoredButton("PLAY", 90, { 490,50 }, { 300,100 });
    mainMenuButtons->makeColoredButton("SETTINGS", 55, { 490,250 }, { 300,100 });
    mainMenuButtons->makeColoredButton("TEST", 90, { 490,450 }, { 300,100 });


    //====================================================================================================TESTING
    TextureLoader tileSets("./res/textures/TileSets");
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(Chunk(tileSets.returnTexture("outdoors.png")));
    chunk->setName("Chunk");

    std::shared_ptr<YSort> ysort = std::make_shared<YSort>(YSort());
    ysort->setName("ysort");

    std::shared_ptr<Node> test = std::make_shared<Node>(Node());
    std::shared_ptr<Container> test_menu = std::make_shared<Container>(Container());
    test->setName("Test");
    test->addChild(chunk);
    game->addLevel(TEST_PLAY, test);
    GUI->addLevel(TEST_PLAY, test_menu);

    std::shared_ptr<ButtonsContainer> testButtons = std::make_shared<ButtonsContainer>(ButtonsContainer(font));
    test_menu->addChild(testButtons);

    std::shared_ptr<CollisionLayer> test_layer = std::make_shared<CollisionLayer>(CollisionLayer());
    std::shared_ptr<Container> test_container = std::make_shared<Container>(Container());
    test_container->setName("test container");

    std::shared_ptr<NPC> testNPC1 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {400,400}, {100,100}, 100, 1));
    testNPC1->setUpByName("Female");
    testNPC1->setCollider(test_layer, {0.0, 25.0}, 30.0);
    ysort->addChild(testNPC1);

    std::shared_ptr<NPC> testNPC2 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {500,400}, {100,100}, 100, 1));
    testNPC2->setUpByName("Male");
    testNPC2->setCollider(test_layer, {0.0, 25.0}, 30.0);
    ysort->addChild(testNPC2);

    std::shared_ptr<NPC> testNPC3 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {600,400}, {100,100}, 100, 1));
    testNPC3->setUpByName("Butcher");
    testNPC3->setCollider(test_layer, {0.0, 25.0}, 30.0);
    ysort->addChild(testNPC3);

    std::shared_ptr<NPC> testNPC4 = std::make_shared<NPC>(NPC(GLOBAL_SOUND_SYSTEM, {700,400}, {100,100}, 100, 1));
    testNPC4->setUpByName("Herald");
    testNPC4->setCollider(test_layer, {0.0, 25.0}, 30.0);
    ysort->addChild(testNPC4);


    std::shared_ptr<Player> player = std::make_shared<Player>(Player(GLOBAL_SOUND_SYSTEM, {100,100}, {100, 100}, 200, 0.55, 0.4));
    player->setName("Player");
    player->setCollider(test_layer, {0.0, 0.0}, 40.0);
    ysort->addChild(player);

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

    player->setIdleAnimation("./res/textures/Player/1-Idle", 0.06);
    player->setRunAnimation("./res/textures/Player/2-Run", 0.06);
    player->setPunchAnimation("./res/textures/Player/7-Attack", 0.05);
    player->setDyingAnimation("./res/textures/Player/12-Hit", 0.05);
    player->setDeadAnimation("./res/textures/Player/14-DeadGround", 0.1);
    player->setDyingSoundName("gunShot.wav");

    testButtons->makeColoredButton("KILL", 90, { 800,50 }, { 300,100 });

    test->setName("Test");
    ysort->addChild(chunk);
    chunk->translate({200.0, 200.0});
 
    //===================================================================================================SETTINGS

    std::shared_ptr<Node> settings = std::make_shared<Node>(Node());
    settings -> setName("Settings");
    GUI->addLevel(SETTINGS, settings);

    std::shared_ptr<ButtonsContainer> resolutionSettings = std::make_shared<ButtonsContainer>(font);
    resolutionSettings->setName("Resolution Settings");
    settings->addChild(resolutionSettings);

    resolutionSettings->translate({ 100, 100 });

    resolutionSettings->makeColoredButton("1280 x 720", 20, { 50,200 }, { 200,100 });
    resolutionSettings->makeColoredButton("1336 x 768", 20, { 300,200 }, { 200,100 });
    resolutionSettings->makeColoredButton("1600 x 900", 20, { 550,200 }, { 200,100 });
    resolutionSettings->makeColoredButton("1920 x 1080", 20, { 800,200 }, { 200,100 });
    resolutionSettings->makeColoredButton("GO BACK", 20, { 350,500 }, { 200,100 });
    
    test -> addChild(cameraController);
  
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
                    std::cout << "button _1920x1080 is: " << (resolutionSettings->get("1920 x 1080")->isActive() ? "active\n" : "inactive\n");
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    root->printTree();
                }
                break;
            }
        }

        if (resolutionSettings->get("1280 x 720")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            root->resize(resolution);
            resolutionSettings->get("1280 x 720")->printDebug();
        }

        if (resolutionSettings->get("1336 x 768")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            root->resize(resolution);
            resolutionSettings->get("1336 x 768")->printDebug();
        }

        if (resolutionSettings->get("1600 x 900")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root->resize(resolution);
            resolutionSettings->get("1600 x 900")->printDebug();
        }

        if (resolutionSettings->get("1920 x 1080")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            root->resize(resolution);
            resolutionSettings->get("1920 x 1080")->printDebug();
        }

        if(mainMenuButtons->get("PLAY")->isPressed(window))
        {
            root->setLevel(GAME);
        }

        if(mainMenuButtons->get("SETTINGS")->isPressed(window))
        {
            root->setLevel(SETTINGS);
        }

        if(mainMenuButtons->get("TEST")->isPressed(window))
        {
            root->setLevel(TEST_PLAY);
        }

        if(resolutionSettings->get("GO BACK")->isPressed(window))
        {
            root->setLevel(MAIN_MENU);
        }

        if(testButtons->get("KILL")->isPressed(window))
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