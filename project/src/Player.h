#pragma once
#include "Lifeform.h"

class Player : public Lifeform
{
public:
	Player();
	~Player();

	void update( float elapsedTime);
	void draw(sf::RenderWindow& rw);

	sf::Vector2f getVelocity();

private:
	sf::Vector2f _velocity;
	sf::Vector2f _maxSpeed;
};

