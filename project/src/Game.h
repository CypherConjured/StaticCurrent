#pragma once
//#include <SFML\Window.hpp>
//#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Level.h"
#include "GameObjectManager.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"

class Game
{
public:
	static void Start();
	static sf::Time GetFrameTime();
	static Level* GetLevel();
	static void nextLevel();
	const static sf::Keyboard& GetInput();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	static sf::View mainView;

private:
	static Level* defineLevels( );
	static bool IsExiting();
	static void GameLoop();
	
	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, ShowingMenu, Playing,
		Paused, StoryMode, BattleMode, NextLevel, Exiting };


	static GameState _gameState;

	static sf::RenderWindow _mainWindow;

	static sf::Clock _clock;
	static sf::Time _frameTime;
	static sf::Time _lastTime;
	static sf::Time _currentTime;

	static Level* _currentLevel;
};

