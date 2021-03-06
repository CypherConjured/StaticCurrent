#pragma once
#include "Lifeform.h"


class BallType :
	public Lifeform
{
public:
	BallType();
	virtual ~BallType();
	void update(float);

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;
	float _startVelocity;

	//float LinearVelocityX(float angle);
	//float LinearVelocityY(float angle);
	sf::Vector2f LinearVelocity(float angle);
};

