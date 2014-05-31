#include "stdafx.h"
#include "Player.h"
#include "Game.h"

using namespace sf;

Player::Player() : _velocity(Vector2f()), _maxSpeed(Vector2f(10.0,10.0)) {
	load("data/player.png");
	assert(isLoaded());
	setHostle(false);
	getSprite().setOrigin(getSprite().getLocalBounds().width/2, getSprite().getLocalBounds().height/2);
}


Player::~Player(){
}

void Player::draw(sf::RenderWindow & rw)
{
    VisibleGameObject::draw(rw);
}

Vector2f Player::getVelocity()
{
    return _velocity;
}

void Player::update(float elapsedTime)
{

    if(Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _velocity.x -= 1.0f;
    }
    if(Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _velocity.x += 1.0f;
    }

	if(Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //do nothing yet.
    }

    if(Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //do nothing yet.
    }

    if(_velocity.x > _maxSpeed.x)
        _velocity.x = _maxSpeed.x;


    if(_velocity.x < -_maxSpeed.x)
        _velocity.x = -_maxSpeed.x;

	if(_velocity.y > _maxSpeed.y)
        _velocity.y = _maxSpeed.y;

    if(_velocity.y < -_maxSpeed.y)
        _velocity.y = -_maxSpeed.y;


    sf::Vector2f pos = this->getPosition();

    if(pos.x  < getSprite().getOrigin().x)
    {
        _velocity.x = _velocity.x * -0.5f; // Bounce by half velocity in opposite direction
		setPosition(getSprite().getOrigin().x,pos.y);
    }else if(pos.x > (Game::SCREEN_WIDTH - getSprite().getOrigin().x)){
		_velocity.x = _velocity.x * -0.5f; // Bounce by half velocity in opposite direction
		setPosition((Game::SCREEN_WIDTH - getSprite().getOrigin().x),pos.y);
	}

    
    getSprite().move(_velocity * elapsedTime);
}
