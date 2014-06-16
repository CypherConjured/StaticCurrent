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
	mainView = _mainWindow.getDefaultView();
	_mainWindow.setView(mainView);
	_mainWindow.setFramerateLimit(60);

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);
	
	soundProvider.PlaySong("data/audio/Glitch.ogg",true);

	Game::_currentLevel = defineLevels();

	Game::_currentLevel->loadLevel();

	_gameState= Game::ShowingSplash;

	_lastTime = _clock.getElapsedTime();

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
					_frameTime = _clock.restart();
					while(_mainWindow.pollEvent(currentEvent))
					{
						if(currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

						if(currentEvent.type == sf::Event::KeyPressed)
						{
							if(currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
						}
					}

					_mainWindow.clear();

					_currentLevel->updateAll( _frameTime );

					_currentLevel->drawAll(_mainWindow);

					_mainWindow.display();

					if(Game::IsExiting()) break;
				}
				break;
			}

		//case Game::NextLevel:
		//	{
		//		if(_currentLevel->isLast()) _gameState = Game::Exiting;
		//		else //nextLevel
		//		break;
		//	}
	}
}

void Game::nextLevel(){
	if(!_currentLevel->isLast()){
		_currentLevel = _currentLevel->_next;
		_currentLevel->loadLevel();
		_currentLevel->GetGameObjectManager().get("Player")->setPosition(_currentLevel->startPosition);
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
Level* Game::GetLevel(){ return _currentLevel; }

// A quirk of C++, static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
sf::View Game::mainView;

sf::Clock Game::_clock;
sf::Time Game::_frameTime;
sf::Time Game::_currentTime;
sf::Time Game::_lastTime;

Level* Game::_currentLevel;

Level* Game::defineLevels( ){
	Level* _currentLevel = new Level(); 
	Level* head = _currentLevel;

	Player* player = new Player();

	//**************** LEVEL 0 *********************
	_currentLevel->levelFile = "data/floor.png";
	_currentLevel->bitmaskFile = "data/floorBitmask.png";
	_currentLevel->startPosition = sf::Vector2f(100,450);
	_currentLevel->GetGameObjectManager().add("Player",player);
	_currentLevel->GetGameObjectManager().get("Player")->setPosition(_currentLevel->startPosition);

	BallType *ball = new BallType();
	ball->setPosition((Game::SCREEN_WIDTH/2),(Game::SCREEN_HEIGHT/2)-15);
	_currentLevel->GetGameObjectManager().add("Ball",ball);
	_currentLevel->startPosition = sf::Vector2f(100,500);

	//**************** LEVEL 1 ********************
	_currentLevel->_next = new Level();
	_currentLevel = _currentLevel->_next;

	_currentLevel->levelFile = "data/floor2m.png";
	_currentLevel->bitmaskFile = "data/floor2mBitmask.png";
	_currentLevel->startPosition = sf::Vector2f(100,600);
	_currentLevel->GetGameObjectManager().add("Player",player);


	//**************** LEVEL 2 ********************
	_currentLevel->_next = new Level();
	_currentLevel = _currentLevel->_next;

	_currentLevel->levelFile = "data/floor2.png";
	_currentLevel->bitmaskFile = "data/floor2Bitmask.png";
	_currentLevel->startPosition = sf::Vector2f(800,600);
	_currentLevel->GetGameObjectManager().add("Player",player);

	return head;
}