#include "stdafx.h"
#include "Player.h"
#include "Game.h"

using namespace sf;

Player::Player(){
	load("data/player.png");
	assert(isLoaded());
	_isFlying = false;
	setHostle(false);
	getSprite().setOrigin(getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height/2);
	setSpeedStat( 10 );
	setStrengthStat( 10 );
}

Player::~Player(){}


void Player::draw(sf::RenderWindow & rw)
{
    VisibleGameObject::draw(rw);
}

void Player::update(float elapsedTime)
{
	sf::Vector2f pos = this->getPosition();
	
	if(_onGround){
		getTargetVelocity().y = 0.0f;
		getTargetVelocity().x = 0.0f;
		if(Keyboard::isKeyPressed(sf::Keyboard::Left)){
			getTargetVelocity().x = -getSpeedStat()*40; // use a speed formula later
		}
		if(Keyboard::isKeyPressed(sf::Keyboard::Right)){
			getTargetVelocity().x = getSpeedStat()*40;
		}
	}
	
	/*else{ //this doesn't work
		if(Keyboard::isKeyPressed(sf::Keyboard::Left)){
			getTargetVelocity().x = -getSpeedStat()*4; 
		}
		if(Keyboard::isKeyPressed(sf::Keyboard::Right)){
			getTargetVelocity().x = getSpeedStat()*4;
		}
	}*/


	if(Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
		if(atExitPoint())
			Game::nextLevel();
    }
	if(Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(!_onGround)
			getTargetVelocity().y += getSpeedStat()*5;
    }

	if(Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(_onGround){
			soundProvider.PlaySound("data/audio/blip.wav");
			getTargetVelocity().y -= getStrengthStat()*160; //Why does it vary?
		}
    }else{
		getTargetVelocity().y += 60; //extra heavy if not holding space
	}

	Lifeform::update(elapsedTime);
}

bool Player::atExitPoint(){
	sf::Vector2f p = getPosition();
	Level* currentLevel = Game::GetLevel();
	if( !currentLevel->getBoundingRect().contains(p))
		return true;

	if(currentLevel->getLevelBitmask().getPixel(p.x,p.y).r < 128){
		return false;
	}else{
		return true;
	}
}
