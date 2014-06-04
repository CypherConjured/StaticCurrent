#include "stdafx.h"
#include "Player.h"
#include "Game.h"

using namespace sf;

Player::Player(){
	load("data/player.png");
	assert(isLoaded());
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

	getTargetVelocity().x = 0.0f;
	getTargetVelocity().y = 0.0f;
	
    if(Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
		getTargetVelocity().x = -getSpeedStat(); // use a speed formula later
    }
    if(Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        getTargetVelocity().x = getSpeedStat();
    }

	if(Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(_onGround){
			getTargetVelocity().y -= getStrengthStat()*20;
		}else{
			getTargetVelocity().y = 0;
		}
    }
    if(Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //impart force down (maybe)
    }

	getTargetVelocity().y += 10.0f;
	calculateVelocity();

    if(pos.x  < getSprite().getOrigin().x){
        _velocity.x = 0;
		setPosition(getSprite().getOrigin().x,pos.y);
    }else if(pos.x > (Game::SCREEN_WIDTH - getSprite().getOrigin().x)){
		_velocity.x = 0;
		setPosition((Game::SCREEN_WIDTH - getSprite().getOrigin().x),pos.y);
	}

    _lastPos = getPosition();
    getSprite().move(_velocity * elapsedTime);
	_onGround = collidesGround();
	if(_onGround)
		setPosition(getPosition().x,_lastPos.y);
}
