#include "stdafx.h"
#include "BallType.h"
#include "Game.h"

BallType::BallType() :
	_velocity(150.0f),
	_startVelocity(150.0f),
	_elapsedTimeSinceStart(0.0f)
{
	load("data/ball.png");
	assert(isLoaded());

	getSprite().setOrigin(15,15);
	
	//sf::Randomizer::SetSeed(std::clock());
	_angle = (float)(rand() % 361 );
}

BallType::~BallType(){ }


void BallType::update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	// Delay game from starting until 3 seconds have passed
	if(_elapsedTimeSinceStart < 3.0f)
		return;

	sf::Vector2f moveAmount = LinearVelocity(_angle) * _velocity  * elapsedTime;
	
	
	//float moveByX = LinearVelocityX(_angle) * moveAmount;
	//float moveByY = LinearVelocityY(_angle) * moveAmount;

	
	//collide with the left/right side of the screen or the top/bottom
	if(getPosition().x + moveAmount.x <= 0 + getWidth()/2 || getPosition().x + getWidth()/2 + moveAmount.x >= Game::SCREEN_WIDTH)
	{
		_velocity += 20.0f;
		_angle = 360.0f - _angle;
		if(_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
		if(_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
		moveAmount.x = -moveAmount.x;
	}else if(getPosition().y - getHeight()/2 <= 0 || getPosition().y + getHeight()/2 + moveAmount.y >= Game::SCREEN_HEIGHT)
	{
		_velocity += 20.0f;
		_angle =  180 - _angle;
		moveAmount.y = -moveAmount.y;
	}


	Player* player = dynamic_cast<Player*>(Game::GetLevel()->GetGameObjectManager().get("Player"));
	if(player != NULL)
	{
		sf::Rect<float> p1BB = player->getBoundingRect();
	
		if(p1BB.intersects(getBoundingRect())) //this is where the ball hits the player
		{ 
			if( !soundProvider.IsSoundPlaying())
				soundProvider.PlaySound("data/audio/kaboom.wav");
			_angle =  360.0f - (_angle - 180.0f);
			if(_angle > 360.0f) _angle -= 360.0f;
		
			moveAmount.y = -moveAmount.y;

			// Make sure ball isn't inside paddle
			if(getBoundingRect().top + getBoundingRect().height > player->getBoundingRect().top)
			{
				//enter battle
				setPosition(getPosition().x,player->getBoundingRect().top - getWidth()/2 -1 );
			}
		
			// Now add "English" based on the players velocity.  
			float playerVelocity = player->getVelocity().x;
		
			if(playerVelocity < 0)
			{
				// moving left
				_angle -= 20.0f;
				if(_angle < 0 ) _angle = 360.0f - _angle;
			}
			else if(playerVelocity > 0)
			{
				_angle += 20.0f;
				if(_angle > 360.0f) _angle = _angle - 360.0f;
			}

			_velocity = _startVelocity;
		}

		getSprite().move(moveAmount);
	}
}

sf::Vector2f BallType::LinearVelocity(float angle)
{
	angle -= 90;
    if (angle < 0) angle = 360 + angle;
	return sf::Vector2f((float)std::cos( angle * ( 3.1415926 / 180.0f )),(float)std::sin( angle * ( 3.1415926 / 180.0f )));
}




