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
	if(Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
		Game::nextLevel();
    }
	if(Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(!_onGround)
			getTargetVelocity().y += getSpeedStat()*40;
    }

	if(Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(_onGround){
			getTargetVelocity().y -= getStrengthStat()*200; //Why so Short?
		}
    }
   

	Lifeform::update(elapsedTime);
}
