#pragma once
#include "Lifeform.h"

class Player : public Lifeform
{
public:
	Player();
	~Player();

	void update( float elapsedTime);
	void draw(sf::RenderWindow& rw);
};

