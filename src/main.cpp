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
#include "ButtonsContainer.hpp"
#include "NPCContainer.hpp"

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

    std::unique_ptr<LevelLoader> root = std::make_unique<LevelLoader>(LevelLoader());
    root->setName("root");

    SoundSystem GLOBAL_SOUND_SYSTEM;

    std::shared_ptr<YSort> ysort = std::make_shared<YSort>(YSort());


    //================================================================================================MAIN MENU
    std::shared_ptr<Node> mainMenu = std::make_shared<Node>(Node());
    mainMenu->setName("Main Menu");
    root->addLevel(mainMenu);
    root->setLevel(0);

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


    std::shared_ptr<Node> test = std::make_shared<Node>(Node());
    test->setName("Test");
    test->addChild(chunk);
    root->addLevel(test);

    std::shared_ptr<ButtonsContainer> testButtons = std::make_shared<ButtonsContainer>(ButtonsContainer(font));
    test->addChild(testButtons);

    std::shared_ptr<CollisionLayer> test_layer = std::make_shared<CollisionLayer>(CollisionLayer());
    std::shared_ptr<NPCContainer> test_NPCContainer = std::make_shared<NPCContainer>(NPCContainer(test_layer, ysort));
    test_NPCContainer->setName("test NPCContainer");
    test_NPCContainer->addChild(ysort);
    test->addChild(test_NPCContainer);
    
    test_NPCContainer->makeNPC("Female", GLOBAL_SOUND_SYSTEM, {400,400}, {100,100});
    test_NPCContainer->makeNPC("Male", GLOBAL_SOUND_SYSTEM, {500,400}, {100,100});
    test_NPCContainer->makeNPC("Butcher", GLOBAL_SOUND_SYSTEM, {600,400}, {100,100});
    test_NPCContainer->makeNPC("Herald", GLOBAL_SOUND_SYSTEM, {700,400}, {100,100});

    std::shared_ptr<Player> player = std::make_shared<Player>(Player(GLOBAL_SOUND_SYSTEM, {100,100}, {100, 100}, 200, 0.55, 0.4));
    player->setName("Player");
    player->setCollider(test_layer, {0.0, 0.0}, 40.0);
    ysort->addChild(player);
    test_NPCContainer->addChild(player);
    std::shared_ptr<CameraController> cameraController = std::make_shared<CameraController>(CameraController(player));

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

    player->setIdleAnimation("./res/textures/Player/1-Idle", 0.06);
    player->setRunAnimation("./res/textures/Player/2-Run", 0.06);
    player->setPunchAnimation("./res/textures/Player/7-Attack", 0.05);
    player->setDyingAnimation("./res/textures/Player/12-Hit", 0.05);
    player->setDeadAnimation("./res/textures/Player/14-DeadGround", 0.1);
    player->setDyingSoundName("gunShot.wav");

    testButtons->makeColoredButton("KILL", 90, { 800,50 }, { 300,100 });

    test->setName("Test");
    root->addLevel(test);
    ysort->addChild(chunk);
    chunk->translate({200.0, 200.0});
 
    //===================================================================================================SETTINGS

    std::shared_ptr<Node> settings = std::make_shared<Node>(Node());
    settings -> setName("Settings");
    root->addLevel(settings);

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
    std::shared_ptr<Node> game = std::make_shared<Node>(Node());
    root->addLevel(game);
    root->printTree();

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

        GLOBAL_SOUND_SYSTEM.update();

        sf::Time delta = deltaClock.restart();
        window.clear();

        root->update(delta);
        root->draw(window);

        sf::View finalView = window.getView();
        
        //std::cout << finalView.getCenter().x << ", " << finalView.getCenter().y << std::endl;
        if(cameraController->isActive())
            finalView.setCenter(cameraController->getView().getCenter());
        window.setView(finalView);
        window.display();
    }
}