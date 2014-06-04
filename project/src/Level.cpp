#include "stdafx.h"
#include "Level.h"
#include "Game.h"

Level::Level(){
	setLevel(0);
	loadLevel();
	assert(isLoaded() && _bitmaskLoaded);

	setPosition(0,0);
	setHostle(false);
}
Level::~Level(){}

void Level::setLevel(int level){
	_levelNum = level;
}

void Level::loadLevel(){
	switch(_levelNum){
	case 1:
		load("put first level here"); 
		
		break;
	default:
		load("data/floor.png");

		if(_bitmask.loadFromFile("data/floor.png")){
			_bitmaskLoaded = true;
		}else{
			_bitmaskLoaded = false;
		}

		break;
	}
}

void Level::draw(sf::RenderWindow & rw){
    //VisibleGameObject::draw(rw);
}

void Level::update( float elapsedTime){ }