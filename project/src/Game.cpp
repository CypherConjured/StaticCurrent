#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "BallType.h"

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;
	
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Wild Bill and the Static Current");
	_mainWindow.setFramerateLimit(60);

	Level* currentLevel = new Level(); // NEEDS TO BE DRAWN FIRST
	_gameObjectManager.add("Level",currentLevel); // FIX NEEDED FOR _GOM


	Player* player1 = new Player();
	player1->setPosition(100,500);
	_gameObjectManager.add("Player",player1);

	BallType *ball = new BallType();
	ball->setPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2)-15);
	_gameObjectManager.add("Ball",ball); // OVERLAPPED BY LEVEL

	_gameState= Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	_frameTime = _clock.restart();
	switch(_gameState)
	{
		case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Game::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
		case Game::Playing:
			{
				sf::Event currentEvent;
				while(_mainWindow.isOpen()){
					while(_mainWindow.pollEvent(currentEvent))
					{
						if(currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

						if(currentEvent.type == sf::Event::KeyPressed)
						{
							if(currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
						}
					}

					_mainWindow.clear();

					_gameObjectManager.updateAll();
					_gameObjectManager.drawAll(_mainWindow);

					_mainWindow.display();

					if(Game::IsExiting()) break;
				}
				break;
			}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
}

sf::Time Game::GetFrameTime(){ return _frameTime; }

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
sf::Clock Game::_clock;
sf::Time Game::_frameTime;
GameObjectManager Game::_gameObjectManager;