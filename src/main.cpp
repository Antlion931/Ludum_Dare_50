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
#include "ButtonsContainer.hpp"
#include "NPCCreator.hpp"
#include "WorldView.hpp"
#include "LevelSetUpper.hpp"

int main()
{
    SoundSystem GLOBAL_SOUND;
    Music GLOBAL_MUSIC;
    GLOBAL_MUSIC.setRepeat(true);
    GLOBAL_MUSIC.stopMusic();

    std::srand(std::time(NULL));
    Resolution resolution(Resolution::resolution::_1280x720);
    sf::RenderWindow window(resolution.getDefault(), "GAME", sf::Style::Close | sf::Style::Titlebar);

    sf::Font font;

    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }


    std::unique_ptr<Root> root = std::make_unique<Root>(Root(GLOBAL_MUSIC));
    root->setName("root");

    std::shared_ptr<LevelLoader> game = std::make_shared<LevelLoader>(LevelLoader(4));
    game->setName("game");
    root->setGame(game);
    
    std::shared_ptr<LevelLoader> GUI = std::make_shared<LevelLoader>(LevelLoader(4));
    GUI->setName("GUI");
    root->setGUI(GUI);

    LevelSetUpper levelSetUpper(game, GUI, font);

    //================================================================================================MAIN MENU
    std::shared_ptr<Node> mainMenuLevel;
    std::shared_ptr<YSort> mainMenuYsort;
    std::shared_ptr<Node> mainMenuLevelGUI;
    std::shared_ptr<ButtonsContainer> mainMenuButtons;
    levelSetUpper.setUp(mainMenuLevel, mainMenuYsort, mainMenuLevelGUI, mainMenuButtons, MAIN_MENU);

    mainMenuButtons->makeColoredButton("PLAY", 90, { 490,50 }, { 300,100 });
    mainMenuButtons->makeColoredButton("SETTINGS", 55, { 490,250 }, { 300,100 });
    mainMenuButtons->makeColoredButton("TEST", 90, { 490,450 }, { 300,100 });
    
    //====================================================================================================TESTING
    std::shared_ptr<Node> testLevel;
    std::shared_ptr<YSort> testYsort;
    std::shared_ptr<Node> testLevelGUI;
    std::shared_ptr<ButtonsContainer> testButtons;
    levelSetUpper.setUp(testLevel, testYsort, testLevelGUI, testButtons, TEST_PLAY); 

    testButtons->makeColoredButton("KILL", 90, { 800,50 }, { 300,100 });

    std::shared_ptr<CollisionLayer> test_layer = std::make_shared<CollisionLayer>(CollisionLayer());
    std::shared_ptr<NPCCreator> test_NPCCreator = std::make_shared<NPCCreator>(NPCCreator(test_layer, testYsort));
    
    test_NPCCreator->makeNPC("Alchemist", GLOBAL_SOUND, {400,400}, {100,100});
    test_NPCCreator->makeNPC("Archer", GLOBAL_SOUND, {500,400}, {100,100});
    test_NPCCreator->makeNPC("Blacksmith", GLOBAL_SOUND, {600,400}, {100,100});
    test_NPCCreator->makeNPC("Butcher", GLOBAL_SOUND, {700,400}, {100,100});
    test_NPCCreator->makeNPC("Female", GLOBAL_SOUND, {800,400}, {100,100});
    test_NPCCreator->makeNPC("Herald", GLOBAL_SOUND, {900,400}, {100,100});
    test_NPCCreator->makeNPC("King", GLOBAL_SOUND, {1000,400}, {100,100});
    test_NPCCreator->makeNPC("Mage", GLOBAL_SOUND, {1100,400}, {100,100});
    test_NPCCreator->makeNPC("Male", GLOBAL_SOUND, {1200,400}, {100,100});
    test_NPCCreator->makeNPC("Merchant", GLOBAL_SOUND, {1300,400}, {100,100});
    test_NPCCreator->makeNPC("Princess", GLOBAL_SOUND, {1400,400}, {100,100});
    test_NPCCreator->makeNPC("Queen", GLOBAL_SOUND, {1500,400}, {100,100});
    test_NPCCreator->makeNPC("Thief", GLOBAL_SOUND, {1600,400}, {100,100});


    TextureLoader tileSets("./res/textures/TileSets");

    std::shared_ptr<Player> player = std::make_shared<Player>(Player(GLOBAL_SOUND));
    player->setCollider(test_layer, {0.0, 31.0}, 20.0);
    testYsort->addChild(player);

    std::shared_ptr<WorldView> worldView = std::make_shared<WorldView>(WorldView(player, tileSets.returnTexture("outdoors.png")));
    worldView->setName("world view");
    testLevel->removeChild(testYsort);
    testLevel->addChild(worldView);
    testLevel->addChild(testYsort);

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

    int index = 0;
 
    //===================================================================================================SETTINGS
    std::shared_ptr<Node> settingsLevel;
    std::shared_ptr<YSort> settingsYsort;
    std::shared_ptr<Node> settingsLevelGUI;
    std::shared_ptr<ButtonsContainer> settingsButtons;
    levelSetUpper.setUp(settingsLevel, settingsYsort, settingsLevelGUI, settingsButtons, SETTINGS);

    settingsButtons->translate({ 100, 100 });

    settingsButtons->makeColoredButton("1280 x 720", 20, { 50,200 }, { 200,100 });
    settingsButtons->makeColoredButton("1336 x 768", 20, { 300,200 }, { 200,100 });
    settingsButtons->makeColoredButton("1600 x 900", 20, { 550,200 }, { 200,100 });
    settingsButtons->makeColoredButton("1920 x 1080", 20, { 800,200 }, { 200,100 });
    settingsButtons->makeColoredButton("GO BACK", 20, { 350,500 }, { 200,100 });

    std::shared_ptr<MouseChangeableProgressbar> volumeBar = std::make_shared<MouseChangeableProgressbar>(MouseChangeableProgressbar(1000.0f, 50.0f, sf::Color(100, 100, 100), sf::Color(200, 200, 200)));
    volumeBar->setName("volume bar");
    volumeBar->setProgress(0.5f);
    settingsLevelGUI->addChild(volumeBar);

    //========================================================================================GAME
    std::shared_ptr<Node> gameLevel;
    std::shared_ptr<YSort> gameYsort;
    std::shared_ptr<Node> gameLevelGUI;
    std::shared_ptr<ButtonsContainer> gameButtons;
    levelSetUpper.setUp(gameLevel, gameYsort, gameLevelGUI, gameButtons, GAME);

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

        if(settingsButtons->get("1280 x 720")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            root->resize(resolution);
            settingsButtons->get("1280 x 720")->printDebug();
        }

        if(settingsButtons->get("1336 x 768")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            root->resize(resolution);
            settingsButtons->get("1336 x 768")->printDebug();
        }

        if(settingsButtons->get("1600 x 900")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root->resize(resolution);
            settingsButtons->get("1600 x 900")->printDebug();
        }

        if(settingsButtons->get("1920 x 1080")->isPressed(window))
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
            GLOBAL_MUSIC.setTrack("GamePlayMusic.wav");
        }

        if(testButtons->get("KILL")->isPressed(window))
        {
            if(index < test_NPCCreator->NPCs.size())
            {
                test_NPCCreator->NPCs[index]->kill();
                index++;
            }
        }

        if(volumeBar->isVisible())
        {
            volumeBar->update(window);
            GLOBAL_MUSIC.setVolume(volumeBar->getProgress() * 50.0f);
            GLOBAL_SOUND.setVolume(volumeBar->getProgress() * 50.0f);
        }

        GLOBAL_SOUND.update();

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