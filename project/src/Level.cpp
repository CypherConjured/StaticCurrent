#include "stdafx.h"
#include "Level.h"
#include "Game.h"

Level::Level(){
	_next = NULL;

	setPosition(0,0);
	setHostle(false);
}
Level::~Level(){
	//delete _gameObjectManager; //?
}

void Level::setLevel(int level){
	_levelNum = level;
}

void Level::loadLevel(){
		load(levelFile);

		if(_bitmask.loadFromFile(bitmaskFile)){
			_bitmaskLoaded = true;
		}else{
			_bitmaskLoaded = false;
		}
		assert(isLoaded() && _bitmaskLoaded);
}

bool Level::isLast(){
	if( this->_next == NULL)
		return true;
	else
		return false;
}

void Level::drawAll(sf::RenderWindow & rw){
    VisibleGameObject::draw(rw);
	_gameObjectManager.drawAll(rw);
}

void Level::updateAll(sf::Time dt){
	_gameObjectManager.updateAll(dt);
}
