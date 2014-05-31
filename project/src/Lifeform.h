#pragma once
#include "VisibleGameObject.h"

class Lifeform : public VisibleGameObject
{
public:
	Lifeform(){};
	~Lifeform(){};

	virtual void update( float elapsedTime) = 0;
	virtual void draw(sf::RenderWindow& rw) = 0;

	virtual sf::Vector2f getVelocity() = 0;

private:
	sf::Vector2f _velocity;
	sf::Vector2f _maxSpeed;
};

