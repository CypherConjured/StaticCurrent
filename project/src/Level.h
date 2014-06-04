#pragma once
#include "VisibleGameObject.h"

class Level : public VisibleGameObject{
public:
	Level();
	~Level();

	void loadLevel();
	void setLevel( int level );
	void update( float elapsedTime);
	void draw(sf::RenderWindow& rw);
	
	sf::Image& getLevelBitmask(){ return _bitmask;}

private:
	int _levelNum;
	sf::Image _bitmask;
	bool _bitmaskLoaded;
	//Level* _next;
};