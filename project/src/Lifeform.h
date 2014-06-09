#pragma once
#include "VisibleGameObject.h"

class Lifeform : public VisibleGameObject
{
public:
	Lifeform();
	~Lifeform();

	virtual void update( float elapsedTime);
	virtual void draw(sf::RenderWindow& rw) = 0;

	virtual sf::Vector2f& getVelocity();
	virtual sf::Vector2f& getTargetVelocity();
	virtual void calculateVelocity();

	void setSpeedStat( int spd ){ _speedStat = spd; }
	int getSpeedStat(){ return _speedStat; }
	void setStrengthStat( int str ){ _strengthStat = str; }
	int getStrengthStat(){ return _strengthStat; }

	bool detectCollisionAtPoint( sf::Vector2f p );
	void attemptMove(float dt );
	bool collidesGround();
	bool _onGround;

	//virtual sf::Vector2f determineTargetSpeed() = 0;

protected:
	sf::Vector2f _lastPos;
	sf::Vector2f _velocity;
	sf::Vector2f _targetVelocity;
	int _speedStat;
	int _strengthStat;
	bool _isFlying;
};

