#pragma once
#include "VisibleGameObject.h"

class Player : public VisibleGameObject
{
public:
	Player();
	~Player();

	void update( float elapsedTime);
	void draw(sf::RenderWindow& rw);

	sf::Vector2f getVelocity() const;

private:
	sf::Vector2f _velocity;
	sf::Vector2f _maxSpeed;
};

