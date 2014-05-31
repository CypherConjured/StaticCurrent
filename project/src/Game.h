#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "GameObjectManager.h"

class Game
{
public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	static sf::Time GetFrameTime();
	const static sf::Keyboard& GetInput();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop();
	
	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, Paused, 
					ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static sf::Clock _clock;
	static sf::Time _frameTime;

	static GameObjectManager _gameObjectManager;
};

