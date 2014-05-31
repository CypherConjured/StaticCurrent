#include "stdafx.h"
#include "BallType.h"
#include "Game.h"

BallType::BallType() :
	_velocity(10.0f),
	_elapsedTimeSinceStart(0.0f)
{
	float _startVelocity = _velocity;
	load("data/ball.png");
	assert(isLoaded());

	getSprite().setOrigin(15,15);
	
	//sf::Randomizer::SetSeed(std::clock());
	_angle = (float)(rand() % 361 );
}


BallType::~BallType()
{
}


void BallType::update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	// Delay game from starting until 3 seconds have passed
	if(_elapsedTimeSinceStart < 3.0f)
		return;

	sf::Vector2f moveAmount = LinearVelocity(_angle) * _velocity  * elapsedTime;
	
	
	//float moveByX = LinearVelocityX(_angle) * moveAmount;
	//float moveByY = LinearVelocityY(_angle) * moveAmount;

	
	//collide with the left or right side of the screen
	if(getPosition().x + moveAmount.x <= 0 + getWidth()/2 || getPosition().x + getWidth()/2 + moveAmount.x >= Game::SCREEN_WIDTH)
	{
		//Ricochet!
		_angle = 360.0f - _angle;
		if(_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
		if(_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
		moveAmount.x = -moveAmount.x;
	}
	


	Player* player1 = dynamic_cast<Player*>(Game::GetGameObjectManager().get("Player"));
	if(player1 != NULL)
	{
		sf::Rect<float> p1BB = player1->getBoundingRect();
	
		if(p1BB.intersects(getBoundingRect()))       //(GetPosition().x + moveAmount.x + (GetSprite().GetSize().x /2),GetPosition().y + (GetSprite().GetSize().y /2) + moveAmount.y))
		{ 
			_angle =  360.0f - (_angle - 180.0f);
			if(_angle > 360.0f) _angle -= 360.0f;
		
		

			moveAmount.y = -moveAmount.y;

			// Make sure ball isn't inside paddle
			if(getBoundingRect().top + getBoundingRect().height > player1->getBoundingRect().top)
			{
				setPosition(getPosition().x,player1->getBoundingRect().top - getWidth()/2 -1 );
			}
		
			// Now add "English" based on the players velocity.  
			float playerVelocity = player1->getVelocity().x;
		
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

			_velocity += 1.0f;
		}

		if(getPosition().y - getHeight()/2 <= 0)
		{
			_angle =  180 - _angle;
			moveAmount.y = -moveAmount.y;
		}

	
		//if(GetPosition().y - GetSprite().GetSize().y/2 - moveAmount.y <= 0 || GetPosition().y + GetSprite().GetSize().y/2 + moveAmount.y >= Game::SCREEN_HEIGHT)
		if(getPosition().y + getHeight()/2 + moveAmount.y >= Game::SCREEN_HEIGHT)
		{
			// move to middle of the screen for now and randomize angle
			getSprite().setPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
			_angle = (float)(rand() % 361 );
			_velocity = _startVelocity;
			_elapsedTimeSinceStart = 0.0f;
		}

		getSprite().move(moveAmount);
	}
}

//float BallType::LinearVelocityX(float angle)
//{
//	angle -= 90;
//    if (angle < 0) angle = 360 + angle;
//		return (float)std::cos( angle * ( 3.1415926 / 180.0f ));
//}
//
//float BallType::LinearVelocityY(float angle)
//{
//	angle -= 90;
//    if (angle < 0) angle = 360 + angle;
//		return (float)std::sin( angle * ( 3.1415926 / 180.0f ));
//}

sf::Vector2f BallType::LinearVelocity(float angle)
{
	angle -= 90;
    if (angle < 0) angle = 360 + angle;
	return sf::Vector2f((float)std::cos( angle * ( 3.1415926 / 180.0f )),(float)std::sin( angle * ( 3.1415926 / 180.0f )));
}




