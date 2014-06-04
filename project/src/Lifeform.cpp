#include "stdafx.h"
#include "Lifeform.h"
#include "Game.h"

Lifeform::Lifeform() : _velocity(sf::Vector2f()), _targetVelocity(sf::Vector2f(0,0)) { }
Lifeform::~Lifeform(){ }

sf::Vector2f& Lifeform::getVelocity(){
	return _velocity;
}

sf::Vector2f& Lifeform::getTargetVelocity(){
	return _targetVelocity;
}

void Lifeform::calculateVelocity(){
	float _a = .2f;
	float _threshold = .01f;

	_velocity = _a * _targetVelocity + (1-_a) * _velocity;

	if (abs(_velocity.x) < _threshold) _velocity.x = 0;
	if (abs(_velocity.y) < _threshold) _velocity.y = 0;
}


bool Lifeform::collidesGround(){
	sf::Sprite mysprite = getSprite();
	int mybot = (int)(getPosition().y + getHeight()/2);
	int minx = (int)(getPosition().x - getWidth()/2);
	int maxx = (int)(getPosition().x + getWidth()/2);
	Level* currentLevel = dynamic_cast<Level*>(Game::GetGameObjectManager().get("Level"));

	if(currentLevel->getLevelBitmask().getPixel(minx,mybot).b > 128 || currentLevel->getLevelBitmask().getPixel(maxx,mybot).b >128){
		return false;
	}else{
		return true;
	}

}
