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
#include "NPCCreator.hpp"

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

    SoundSystem GLOBAL_SOUND_SYSTEM;

    std::unique_ptr<Root> root = std::make_unique<Root>(Root());
    root->setName("root");

    std::shared_ptr<LevelLoader> game = std::make_shared<LevelLoader>(LevelLoader(4));
    game->setName("game");
    root->setGame(game);
    
    std::shared_ptr<LevelLoader> GUI = std::make_shared<LevelLoader>(LevelLoader(4));
    GUI->setName("gui");
    root->setGUI(GUI);

    //================================================================================================MAIN MENU
    std::shared_ptr<Node> mainMenuLevel = std::make_shared<Node>(Node());
    mainMenuLevel->setName("main menu level");
    game->addLevel(MAIN_MENU, mainMenuLevel);

    std::shared_ptr<YSort> mainMenuYsort = std::make_shared<YSort>(YSort());
    mainMenuYsort->setName("main menu Ysort");
    mainMenuLevel->addChild(mainMenuYsort);

    std::shared_ptr<Node> mainMenuLevelGUI = std::make_shared<Node>(Node());
    mainMenuLevelGUI ->setName("main menu level GUI");
    GUI->addLevel(MAIN_MENU, mainMenuLevelGUI);

    std::shared_ptr<ButtonsContainer> mainMenuButtons = std::make_shared<ButtonsContainer>(ButtonsContainer(font));
    mainMenuButtons->setName("main menu buttons");
    mainMenuLevelGUI->addChild(mainMenuButtons);

    mainMenuButtons->makeColoredButton("PLAY", 90, { 490,50 }, { 300,100 });
    mainMenuButtons->makeColoredButton("SETTINGS", 55, { 490,250 }, { 300,100 });
    mainMenuButtons->makeColoredButton("TEST", 90, { 490,450 }, { 300,100 });

    //====================================================================================================TESTING
    std::shared_ptr<Node> testLevel = std::make_shared<Node>(Node());
    testLevel->setName("test level");
    game->addLevel(TEST_PLAY, testLevel);

    std::shared_ptr<YSort> testYsort = std::make_shared<YSort>(YSort());
    testYsort->setName("test Ysort");
    testLevel->addChild(testYsort);

    std::shared_ptr<Node> testLevelGUI = std::make_shared<Node>(Node());
    testLevelGUI->setName("test level GUI");
    GUI->addLevel(TEST_PLAY, testLevelGUI);

    std::shared_ptr<ButtonsContainer> testButtons = std::make_shared<ButtonsContainer>(ButtonsContainer(font));
    testButtons->setName("test buttons");
    testLevelGUI->addChild(testButtons);

    testButtons->makeColoredButton("KILL", 90, { 800,50 }, { 300,100 });

    TextureLoader tileSets("./res/textures/TileSets");
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(Chunk(tileSets.returnTexture("outdoors.png")));
    chunk->setName("Chunk");
    testYsort ->addChild(chunk);

    std::shared_ptr<CollisionLayer> test_layer = std::make_shared<CollisionLayer>(CollisionLayer());
    std::shared_ptr<NPCCreator> test_NPCCreator = std::make_shared<NPCCreator>(NPCCreator(test_layer, testYsort));
    
    test_NPCCreator->makeNPC("Female", GLOBAL_SOUND_SYSTEM, {400,400}, {100,100});
    test_NPCCreator->makeNPC("Male", GLOBAL_SOUND_SYSTEM, {500,400}, {100,100});
    test_NPCCreator->makeNPC("Butcher", GLOBAL_SOUND_SYSTEM, {600,400}, {100,100});
    test_NPCCreator->makeNPC("Herald", GLOBAL_SOUND_SYSTEM, {700,400}, {100,100});

    std::shared_ptr<Player> player = std::make_shared<Player>(Player(GLOBAL_SOUND_SYSTEM, {100,100}, {100, 100}, 200, 0.55, 0.4));
    player->setName("Player");
    player->setIdleAnimation("./res/textures/Player/1-Idle", 0.06);
    player->setRunAnimation("./res/textures/Player/2-Run", 0.06);
    player->setPunchAnimation("./res/textures/Player/7-Attack", 0.05);
    player->setDyingAnimation("./res/textures/Player/12-Hit", 0.05);
    player->setDeadAnimation("./res/textures/Player/14-DeadGround", 0.1);
    player->setDyingSoundName("gunShot.wav");
    player->setCollider(test_layer, {0.0, 0.0}, 40.0);
    testYsort->addChild(player);

    std::shared_ptr<CameraController> cameraController = std::make_shared<CameraController>(CameraController(player));
    cameraController->setName("Player's camera control");
    player->addChild(cameraController);

    std::shared_ptr<Collidable> obstacle_1 = std::make_shared<Collidable>(Collidable());
    obstacle_1->setName("obstacle 1");
    obstacle_1->setCollider(test_layer, {0, 0}, 50.0);
    obstacle_1->setTranslation({500, 500});
    testYsort->addChild(obstacle_1);

    std::shared_ptr<Collidable> obstacle_2 = std::make_shared<Collidable>(Collidable());
    obstacle_2->setName("obstacle 2");
    obstacle_2->setCollider(test_layer, {0, 0}, 50.0);
    obstacle_2->setTranslation({550, 500});
    testYsort->addChild(obstacle_2);

    std::shared_ptr<Collidable> obstacle_3 = std::make_shared<Collidable>(Collidable());
    obstacle_3->setName("obstacle 3");
    obstacle_3->setCollider(test_layer, {0, 0}, {100.0, 50.0});
    obstacle_3->setTranslation({700, 500});
    obstacle_3->scale({2.0,2.0});
    testYsort->addChild(obstacle_3);

    chunk->translate({200.0, 200.0});
 
    //===================================================================================================SETTINGS
    std::shared_ptr<Node> settingsLevel = std::make_shared<Node>(Node());
    settingsLevel->setName("settings level");
    game->addLevel(SETTINGS, settingsLevel);

    std::shared_ptr<YSort> settingsYsort = std::make_shared<YSort>(YSort());
    settingsYsort->setName("game Ysort");
    settingsLevel->addChild(settingsYsort);

    std::shared_ptr<Node> settingsLevelGUI = std::make_shared<Node>(Node());
    settingsLevelGUI -> setName("settings level GUI");
    GUI->addLevel(SETTINGS, settingsLevelGUI);

    std::shared_ptr<ButtonsContainer> settingsButtons = std::make_shared<ButtonsContainer>(font);
    settingsButtons->setName("settings buttons");
    settingsLevelGUI->addChild(settingsButtons);

    settingsButtons->translate({ 100, 100 });

    settingsButtons->makeColoredButton("1280 x 720", 20, { 50,200 }, { 200,100 });
    settingsButtons->makeColoredButton("1336 x 768", 20, { 300,200 }, { 200,100 });
    settingsButtons->makeColoredButton("1600 x 900", 20, { 550,200 }, { 200,100 });
    settingsButtons->makeColoredButton("1920 x 1080", 20, { 800,200 }, { 200,100 });
    settingsButtons->makeColoredButton("GO BACK", 20, { 350,500 }, { 200,100 });
    
    //test -> addChild(cameraController);
  
    //========================================================================================GAME
    std::shared_ptr<Node> gameLevel = std::make_shared<Node>(Node());
    gameLevel->setName("game level");
    game->addLevel(GAME, gameLevel);

    std::shared_ptr<YSort> gameYsort = std::make_shared<YSort>(YSort());
    gameYsort->setName("game Ysort");
    gameLevel->addChild(gameYsort);

    std::shared_ptr<Node> gameLevelGUI = std::make_shared<Node>(Node());
    gameLevelGUI->setName("game level GUI");
    GUI->addLevel(GAME, gameLevelGUI);

    std::shared_ptr<ButtonsContainer> gameButtons = std::make_shared<ButtonsContainer>(ButtonsContainer(font));
    gameButtons->setName("game buttons");
    gameLevelGUI->addChild(gameButtons);


    //=========================================================================================GAME LOOP
    root->setLevel(MAIN_MENU);
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
                    std::cout << "button _1920x1080 is: " << (settingsButtons->get("1920 x 1080")->isActive() ? "active\n" : "inactive\n");
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    root->printTree();
                }
                break;
            }
        }

        if (settingsButtons->get("1280 x 720")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            root->resize(resolution);
            settingsButtons->get("1280 x 720")->printDebug();
        }

        if (settingsButtons->get("1336 x 768")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            root->resize(resolution);
            settingsButtons->get("1336 x 768")->printDebug();
        }

        if (settingsButtons->get("1600 x 900")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root->resize(resolution);
            settingsButtons->get("1600 x 900")->printDebug();
        }

        if (settingsButtons->get("1920 x 1080")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            root->resize(resolution);
            settingsButtons->get("1920 x 1080")->printDebug();
        }

        if(settingsButtons->get("GO BACK")->isPressed(window))
        {
            root->setLevel(MAIN_MENU);
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

        if(testButtons->get("KILL")->isPressed(window))
        {
            player->kill();
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