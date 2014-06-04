#pragma once
#include "VisibleGameObject.h"

class Lifeform : public VisibleGameObject
{
public:
	Lifeform();
	~Lifeform();

	virtual void update( float elapsedTime) = 0;
	virtual void draw(sf::RenderWindow& rw) = 0;

	virtual sf::Vector2f& getVelocity();
	virtual sf::Vector2f& getTargetVelocity();
	virtual void calculateVelocity();

	virtual void setSpeedStat( int spd ){ _speedStat = spd; }
	virtual int getSpeedStat(){ return _speedStat; }
	virtual void setStrengthStat( int str ){ _strengthStat = str; }
	virtual int getStrengthStat(){ return _strengthStat; }
	bool collidesGround();
	bool _onGround;
	//virtual sf::Vector2f determineTargetSpeed() = 0;

protected:
	sf::Vector2f _velocity;
	sf::Vector2f _targetVelocity;
	int _speedStat;
	int _strengthStat;
};

