#include "Game.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "GameObjectManager.h"
#include "BGObject.h"
#include "CarPlayer.h"
#include "MainMenuScreen.h"
#include "FontManager.h"
#include "ApplicationManager.h"
#include "HUDScreen.h"

#include "EnemyCar_A.h"
#include "GameObjectPool.h"
#include "EmptyGameObject.h"
#include "EnemySwarmHandler_A.h"

#include "MainMenuScene.h"
#include "SceneManager.h"

#include "GameScene.h"
#include "GameScene2.h"
#include "GameScene2.h"
#include "GameScene3.h"

#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "AudioManager.h"

Game::Game() :
    Window(sf::VideoMode({ Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT }), "Road Fighter") {
    TextureManager::getInstance()->loadAll();
    AudioManager::getInstance()->loadAll();
    FontManager::getInstance()->loadAll();
    ApplicationManager::getInstance()->initialize(&this->Window);

    //reigster scemes
    SceneManager::getInstance()->registerScene(new MainMenuScene());
    SceneManager::getInstance()->registerScene(new GameScene());
    SceneManager::getInstance()->registerScene(new GameScene2());
    SceneManager::getInstance()->registerScene(new GameScene3());
    //gameoverscreen not done



    //load first scene
    SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);

    /*Comment out

    BGObject* bgObject = new BGObject("BGObject");
    GameObjectManager::getInstance()->addObject(bgObject);

    CarPlayer* planeObject = new CarPlayer("PlayerObject");
    GameObjectManager::getInstance()->addObject(planeObject);


    AirplaneSupport* support1 = new AirplaneSupport("AirSupport_1");
    planeObject->attachChild(support1);
    support1->setPosition(50, 100);

    AirplaneSupport* support2 = new AirplaneSupport("AirSupport_2");
    planeObject->attachChild(support2);
    support2->setPosition(-50, 100);

    HUDScreen* hudScreen = new HUDScreen("HUDScreen");
    GameObjectManager::getInstance()->addObject(hudScreen);

    //create N enemies via object pooling
    srand(time(NULL));
    EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
    EnemySwarmHandler_A* swarmHandler = new EnemySwarmHandler_A(200, "SwarmHandler");
    enemiesManager->attachComponent(swarmHandler);
    GameObjectManager::getInstance()->addObject(enemiesManager);
   */

   /*MainMenuScreen* mainMenuScreen = new MainMenuScreen("MainMenuScreen");
   GameObjectManager::getInstance()->addObject(mainMenuScreen);*/

};


void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; // set time to zero

    while (Window.isOpen()) {

        processEvents();
        timeSinceLastUpdate += clock.restart(); // returns last value then restart
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
        SceneManager::getInstance()->checkLoadScene();
    }
}

void Game::processEvents() {
    while (const std::optional event = Window.pollEvent()) {
        if (event->is<sf::Event::Closed>() ||
            (event->is<sf::Event::KeyPressed>() &&
                event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
            Window.close();
        else
            GameObjectManager::getInstance()->processInput(event);
    }
}

void Game::update(sf::Time deltaTime) {
    if (!ApplicationManager::getInstance()->isPaused()) {
        GameObjectManager::getInstance()->update(deltaTime);
        PhysicsManager::getInstance()->perform();
        ScoreManager::getInstance()->perform();
        SceneManager::getInstance()->checkLoadScene();
    }
}

void Game::render() {
    Window.clear();
    GameObjectManager::getInstance()->draw(&Window);
    Window.display();
}

