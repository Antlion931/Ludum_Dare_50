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
#include "DialogueBox.hpp"
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
#include "DialogueBox.hpp"
#include "Toolkit.hpp"
#include "StaticObject.hpp"
#include "EntityPrefabs.hpp"
#include "QuestCreator.hpp"
#include "TextBox.hpp"
#include "Cutescene.hpp"

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

    NPC::font = font;

    std::unique_ptr<Root> root = std::make_unique<Root>(Root(GLOBAL_MUSIC));
    root->setName("root");

    std::shared_ptr<LevelLoader> game = std::make_shared<LevelLoader>(LevelLoader(4));
    game->setName("game");
    root->setGame(game);
    
    std::shared_ptr<LevelLoader> GUI = std::make_shared<LevelLoader>(LevelLoader(4));
    GUI->setName("GUI");
    root->setGUI(GUI);

    LevelSetUpper levelSetUpper(game, GUI, font, &GLOBAL_SOUND);

    //================================================================================================MAIN MENU
    std::shared_ptr<Node> mainMenuLevel;
    std::shared_ptr<Node> mainMenuLevelGUI;
    std::shared_ptr<ButtonsContainer> mainMenuButtons;
    levelSetUpper.setUp(mainMenuLevel, mainMenuLevelGUI, mainMenuButtons, MAIN_MENU);

    std::shared_ptr<Button> background = std::make_shared<Button>(Button({0,0}, {1280, 720}));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./res/textures/background/background.jpg");
    background->box.setTexture(&backgroundTexture);
    mainMenuLevelGUI->addChild(background);
    background->setName("back ground");
    

    mainMenuLevelGUI->removeChild(mainMenuButtons);
    mainMenuLevelGUI->addChild(mainMenuButtons);

    mainMenuButtons->makeColoredButton("PLAY", 60, { 850,150 }, { 350,80 });
    mainMenuButtons->makeColoredButton("SETTINGS", 60, { 850,300 }, { 350,80 });
    //mainMenuButtons->makeColoredButton("TEST", 60, { 850,450 }, { 350,80 });
    mainMenuButtons->makeColoredButton("EXIT", 60, {850, 600}, {350,80});
    
    //====================================================================================================TESTING
    std::shared_ptr<Node> testLevel;
    std::shared_ptr<Node> testLevelGUI;
    std::shared_ptr<ButtonsContainer> testButtons;
    levelSetUpper.setUp(testLevel, testLevelGUI, testButtons, TEST_PLAY); 
    
    TextureLoader tileSets("./res/textures/TileSets");
    std::shared_ptr<Player> player = std::make_shared<Player>(Player(GLOBAL_SOUND));
    player->scale({1.6, 1.6});
    

    std::shared_ptr<WorldView> worldView = std::make_shared<WorldView>(WorldView(GLOBAL_SOUND, player, tileSets.returnTexture("outdoors.png")));
    worldView->setName("world view");
    testLevel->addChild(worldView);

    std::shared_ptr<QuestCreator> questCreator = std::make_shared<QuestCreator>(player, worldView->loadedObjects);
    NPC::setQuestCreator(questCreator);

    testButtons->makeColoredButton("TRY AGAIN", 90, {390, 550}, {500, 100});
    testButtons->makeColoredButton("MENU", 30, {25,25}, {200,50});

    std::shared_ptr<TextBox> testQuestBox = std::make_shared<TextBox>(TextBox({490, 90}, {200, 60}, sf::Text("Place holder", font, 40)));
    testLevelGUI->addChild(testQuestBox);

    std::shared_ptr<TextBox> testTimeBox = std::make_shared<TextBox>(TextBox({490, 20}, {200, 60}, sf::Text("Place holder", font, 40)));
    testLevelGUI->addChild(testTimeBox);

    std::shared_ptr<TextBox> testScoreBox = std::make_shared<TextBox>(TextBox({1100, 20}, {100, 60}, sf::Text("Place holder", font, 40)));
    testLevelGUI->addChild(testScoreBox);

    std::shared_ptr<TextBox> testInfoBox = std::make_shared<TextBox>(TextBox({550, 300}, {200, 60}, sf::Text("New Quest!", font, 60)));
    testLevelGUI->addChild(testInfoBox);
    
    std::shared_ptr<CameraController> cameraController = std::make_shared<CameraController>(CameraController(player));
    cameraController->setName("Player's camera control");
    player->addChild(cameraController);
 
    //===================================================================================================SETTINGS
    std::shared_ptr<Node> settingsLevel;
    std::shared_ptr<Node> settingsLevelGUI;
    std::shared_ptr<ButtonsContainer> settingsButtons;
    levelSetUpper.setUp(settingsLevel, settingsLevelGUI, settingsButtons, SETTINGS);

    settingsButtons->makeColoredButton("1280 x 720", 60, { 100,150 }, { 450,120 });
    settingsButtons->makeColoredButton("1336 x 768", 60, { 100,350 }, { 450,120 });
    settingsButtons->makeColoredButton("1600 x 900", 60, { 100,550 }, { 450,120 });
    settingsButtons->makeColoredButton("1920 x 1080", 60, { 720,150 }, { 450,120 });
    settingsButtons->makeColoredButton("2048 x 1152", 60, { 720,350 }, { 450,120 });
    settingsButtons->makeColoredButton("3072 x 1728", 60, { 720,550 }, { 450,120 });
    settingsButtons->makeColoredButton("GO BACK", 30, { 1000,30 }, { 170,50 });

    std::shared_ptr<MouseChangeableProgressbar> volumeBar = std::make_shared<MouseChangeableProgressbar>(MouseChangeableProgressbar(800.0f, 50.0f, sf::Color(242,196,22), sf::Color(1,2,4), 20, sf::Color(1,2,4)));
    volumeBar->setName("volume bar");
    volumeBar->setProgress(0.2f);
    volumeBar->setPosition({100, 30});
    settingsLevelGUI->addChild(volumeBar);

    GLOBAL_MUSIC.setVolume(volumeBar->getProgress() * 50.0f);
    GLOBAL_SOUND.setVolume(volumeBar->getProgress() * 70.0f);

    //========================================================================================CUTSCENE
    std::shared_ptr<Node> cutsceneLevel;
    std::shared_ptr<Node> cutsceneLevelGUI;
    std::shared_ptr<ButtonsContainer> cutsceneButtons;
    levelSetUpper.setUp(cutsceneLevel, cutsceneLevelGUI, cutsceneButtons, CUTSCENE);

    sf::Texture texture1;
    texture1.loadFromFile("./res/cutescene/1.png");

    sf::Texture texture2;
    texture2.loadFromFile("./res/cutescene/2.png");

    sf::Texture texture3;
    texture3.loadFromFile("./res/cutescene/3.png");
    
    std::shared_ptr<Cutescene> cutescene = std::make_shared<Cutescene>(Cutescene({0,0}, {1280, 720}, &texture1, &texture2, &texture3));
    cutescene->setName("cute scene");
    cutsceneLevelGUI->addChild(cutescene);

    cutsceneLevelGUI->removeChild(cutsceneButtons);
    cutsceneLevelGUI->addChild(cutsceneButtons);

    //=========================================================================================GAME LOOP
    root->setLevel(MAIN_MENU);
    sf::Clock deltaClock;

    bool has_lost = false;

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
                // else if (event.key.code == sf::Keyboard::Space)
                // {
                //     root->printTree();
                // }
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

        if(settingsButtons->get("2048 x 1152")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_2048x1152, window);
            root->resize(resolution);
            settingsButtons->get("2048 x 1152")->printDebug();
        }

        if(settingsButtons->get("3072 x 1728")->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_3072x1728, window);
            root->resize(resolution);
            settingsButtons->get("3072 x 1728")->printDebug();
        }

        if(settingsButtons->get("GO BACK")->isPressed(window))
        {
            root->setLevel(MAIN_MENU);
        }

        if(mainMenuButtons->get("PLAY")->isPressed(window))
        {
            root->setLevel(CUTSCENE);
            GLOBAL_SOUND.playSound("notification.wav");
        }

        if(mainMenuButtons->get("SETTINGS")->isPressed(window))
        {
            root->setLevel(SETTINGS);
        }

        // if(mainMenuButtons->get("TEST")->isPressed(window))
        // {
        //     root->setLevel(TEST_PLAY);
        //     //questCreator->addQuest(Quest(test_NPCCreator->NPCs.at(0).get(),kill));
        //     GLOBAL_MUSIC.setTrack("GamePlayMusic.wav");
        // }

        // if(testButtons->get("KILL")->isPressed(window))
        // {
        //     if(index < test_NPCCreator->NPCs.size())
        //     {
        //         test_NPCCreator->NPCs[index]->kill();
        //         index++;
        //     }
        // }
        if(mainMenuButtons->get("EXIT")->isPressed(window))
        {
            window.close();
        }

        if(testButtons->get("TRY AGAIN")->isPressed(window))
        {
            player = std::make_shared<Player>(Player(GLOBAL_SOUND));
            player->scale({1.6, 1.6});
            cameraController = std::make_shared<CameraController>(CameraController(player));
            cameraController->setName("Player's camera control");
            player->addChild(cameraController);

            testLevel->removeChild(worldView);
            worldView = std::make_shared<WorldView>(WorldView(GLOBAL_SOUND, player, tileSets.returnTexture("outdoors.png")));
            testLevel->addChild(worldView);
            has_lost = false;
            questCreator->failedQuests.clear();
            testInfoBox->setText("New Quest!");
            GLOBAL_MUSIC.playMusic();
        }

        if(testButtons->get("MENU")->isPressed(window))
        {
            root->setLevel(MAIN_MENU);
        }

        if(volumeBar->isVisible())
        {
            volumeBar->update(window);
            GLOBAL_MUSIC.setVolume(volumeBar->getProgress() * 50.0f);
            GLOBAL_SOUND.setVolume(volumeBar->getProgress() * 70.0f);
        }

        if(cutescene->isVisible())
        {
            if(cutescene->isCutesceneEnded())
            {
                root->setLevel(TEST_PLAY);
            }
        }

        GLOBAL_SOUND.update();
        if (player->isActive())
            questCreator->update();

        sf::Time delta = deltaClock.restart();
        window.clear(sf::Color(242,196,22));

        if(player->isActive() && !has_lost)
        {
            if(testScoreBox->isVisible())
            {
                testScoreBox->setString("SCORE: " + std::to_string(questCreator->completedQuests.size())); 
            }
            if(testQuestBox->isVisible())
            {
                testQuestBox->setString(Quest::questTypeToString(questCreator->activeQuests[0].returnQuestType()) + ": " + questCreator->activeQuests[0].returnQuestObjectiveType()); 
            }
            if(testTimeBox->isVisible())
            {
                testTimeBox->setString("Remaining " + std::to_string(questCreator->activeQuests[0].returnRemainingTime().asSeconds()) + " s"); 
            }
            if(questCreator->activeQuests[0].returnRemainingTime().asSeconds() > 28.0)
            {
                testInfoBox->setVisible(1);
            }
            else
            {
                testInfoBox->setVisible(0);
            }

            if(questCreator->failedQuests.size() != 0)
            {
                player->kill();
                testButtons->get("TRY AGAIN")->setVisible(1);
                testButtons->get("TRY AGAIN")->setActive(1);
                testTimeBox->setString("");
                testQuestBox->setString("");
                testInfoBox->setText("You lost!");
                testInfoBox->setVisible(1);
                has_lost = true;
                GLOBAL_MUSIC.stopMusic();
            }
            else 
            {
                testButtons->get("TRY AGAIN")->setVisible(0);
                testButtons->get("TRY AGAIN")->setActive(0);
            }
        }

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