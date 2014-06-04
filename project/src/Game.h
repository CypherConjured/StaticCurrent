#pragma once
//#include <SFML\Window.hpp>
//#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Level.h"
#include "GameObjectManager.h"

class Game
{
public:
	static void Start();
	static GameObjectManager& GetGameObjectManager(){ return _gameObjectManager; }
	static sf::Time GetFrameTime();
	const static sf::Keyboard& GetInput();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	//static sf::RenderWindow _mainWindow; // remove this line

private:
	static bool IsExiting();
	static void GameLoop();
	
	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, Paused, 
					ShowingMenu, Playing, Exiting };


	static GameState _gameState;
	static sf::RenderWindow _mainWindow; //put this one back

	static sf::Clock _clock;
	static sf::Time _frameTime;

	static GameObjectManager _gameObjectManager;
};

