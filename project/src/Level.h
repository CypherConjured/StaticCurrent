#pragma once
#include "VisibleGameObject.h"
#include "GameObjectManager.h"

class Level : public VisibleGameObject{
public:
	Level();
	~Level();

	void loadLevel();
	void setLevel( int level );
	void updateAll( sf::Time elapsedTime);
	void drawAll(sf::RenderWindow& rw);

	bool isLast();
	Level* _next;

	std::string levelFile;
	std::string bitmaskFile;

	sf::Vector2f startPosition;
	
	sf::Image& getLevelBitmask(){ return _bitmask;}
	GameObjectManager& GetGameObjectManager(){ return _gameObjectManager; }

private:
	int _levelNum;
	sf::Image _bitmask;
	bool _bitmaskLoaded;
	
	GameObjectManager _gameObjectManager;
};