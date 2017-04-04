#include "stdafx.h"
#include "Lifeform.h"
#include "Game.h"

Lifeform::Lifeform() : _velocity(sf::Vector2f()), _targetVelocity(sf::Vector2f(0,0)) { }
Lifeform::~Lifeform(){ }

void Lifeform::draw(sf::RenderWindow & renderWindow)
{
	VisibleGameObject::draw(renderWindow);
}

sf::Vector2f& Lifeform::getVelocity(){
	return _velocity;
}

sf::Vector2f& Lifeform::getTargetVelocity(){
	return _targetVelocity;
}

void Lifeform::update( float dt ){
	sf::Vector2f pos = this->getPosition();

	if(!_onGround && !_isFlying)
		getTargetVelocity().y += 80.0f;

	calculateVelocity();

	if(pos.y < getHeight()/2) setPosition(pos.x,getHeight()/2);
	if(pos.y > Game::SCREEN_WIDTH - getHeight()/2 ) setPosition(pos.x,Game::SCREEN_WIDTH - getHeight()/2);
    if(pos.x  < getSprite().getOrigin().x){
        _velocity.x = 0;
		setPosition(getSprite().getOrigin().x,pos.y);
    }else if(pos.x > (Game::SCREEN_WIDTH - getSprite().getOrigin().x)){
		_velocity.x = 0;
		setPosition((Game::SCREEN_WIDTH - getSprite().getOrigin().x),pos.y);
	}
    _lastPos = getPosition();

	attemptMove( dt );
	
	//BUGGY Collisions  \/ \/ \/
	//getSprite().move(sf::Vector2f(0,_velocity.y) * dt);
	//_onGround = collidesGround();

	//if(_onGround)
		//setPosition(getPosition().x,_lastPos.y);
} 

void Lifeform::calculateVelocity(){
	float _a = .2f;
	float _threshold = .01f;

	_velocity = _a * _targetVelocity + (1-_a) * _velocity;

	if (abs(_velocity.x) < _threshold) _velocity.x = 0;
	if (abs(_velocity.y) < _threshold) _velocity.y = 0;
}


bool Lifeform::collidesGround(){ //Avoid using this... Why? I have no clue. Thanks past self!
	int mybot = static_cast<int>(getPosition().y + getHeight()/2);
	int mytop = static_cast<int>(getPosition().y - getHeight()/2);
	int minx = static_cast<int>(getPosition().x - getWidth()/2);
	int maxx = static_cast<int>(getPosition().x + getWidth()/2);
	Level* currentLevel = Game::GetLevel();
	
	sf::Vector2f p(maxx,mybot);
	if( !currentLevel->getBoundingRect().contains(p))
		return true;

	if(currentLevel->getLevelBitmask().getPixel(minx,mybot).b < 128 || currentLevel->getLevelBitmask().getPixel(maxx,mybot).b < 128){
		return false;
	}else{
		return true;
	}
}

bool Lifeform::detectCollisionAtPoint( sf::Vector2f p ){
	Level* currentLevel = Game::GetLevel();
	if( !currentLevel->getBoundingRect().contains(p))
		return true;

	if(currentLevel->getLevelBitmask().getPixel(p.x,p.y).b < 128){
		return false;
	}else{
		return true;
	}
}

void Lifeform::attemptMove( float dt ){

	_lastPos = getPosition();
	float dirx = _velocity.x * dt;
	float diry = _velocity.y * dt;

	//IF youre moving mostly horizontal, check horizontal collision first
	//TODO: Why am I doing this???
	if( abs(dirx) >= abs(diry) ){
		findHorizontalCollision(dt); //returns a bool. TODO: error handling. 

		findVerticalCollision(dt); //returns a bool. TODO: error handling.

	}else{

		findVerticalCollision(dt); //returns a bool. TODO: error handling.

		findHorizontalCollision(dt); //returns a bool. TODO: error handling.
	}
}

bool Lifeform::findVerticalCollision(float dt){

	int mybot = static_cast<int>(getPosition().y + getHeight() / 2);
	int mytop = static_cast<int>(getPosition().y - getHeight() / 2);
	int minx = static_cast<int>(getPosition().x - getWidth() / 2);
	int maxx = static_cast<int>(getPosition().x + getWidth() / 2);

	float diry = _velocity.y * dt;

	sf::Vector2f atm = sf::Vector2f(0, 0);

	for (float y = 0; y <= abs(diry); y++){
		if (diry > 0){
			if (!detectCollisionAtPoint(sf::Vector2f(maxx, mybot + y)) && !detectCollisionAtPoint(sf::Vector2f(minx, mybot + y))){
				_onGround = false;
				atm = sf::Vector2f(0, y);
			}
			else
				_onGround = true;
		}
		else{
			if (!detectCollisionAtPoint(sf::Vector2f(maxx, mytop - y)) && !detectCollisionAtPoint(sf::Vector2f(minx, mytop - y))){
				atm = sf::Vector2f(0, -y);
				//TODO: cut off the _velocity.y for the jump when hitting a ceiling. 
				_onGround = false;
			}
			else{
				_targetVelocity.y = -.4 * _velocity.y;
				_velocity.y = 0;
			}
		}
	}
	
	//checking for out of bounds
	if (!((atm.y + _lastPos.y) < Game::SCREEN_HEIGHT)
		|| !((atm.y + _lastPos.y) >= 0)
		|| !((atm.x + _lastPos.x) < Game::SCREEN_WIDTH)
		|| !((atm.x + _lastPos.x) >= 0)) return false;

	getSprite().move(atm);

	return true;
}

bool Lifeform::findHorizontalCollision(float dt){
	int mybot = static_cast<int>(getPosition().y + getHeight() / 2);
	int mytop = static_cast<int>(getPosition().y - getHeight() / 2);
	int minx = static_cast<int>(getPosition().x - getWidth() / 2);
	int maxx = static_cast<int>(getPosition().x + getWidth() / 2);

	float dirx = _velocity.x * dt;
	float diry = _velocity.y * dt;

	//This is the final movement vector.
	sf::Vector2f atm = sf::Vector2f(0, 0);

	//These are for determining the max movement in a given direction.
	//Note how they match the for loops below.
	float mx = 0.0f;
	float my = 5.0f;

		//Check collision in the direction of travel 
		for (float x = 0; x <= abs(dirx); x++){
			for (float y = 5; y >= 0; y--){
				//Are you going right or left?
				if (dirx > 0){
					if (!detectCollisionAtPoint(sf::Vector2f(maxx + x, mybot - y)))
						if (mx < abs(x) && y < my){
							mx = abs(x);
							my = y;
							atm = sf::Vector2f(x, -y);
						}
				}
				else{
					if (!detectCollisionAtPoint(sf::Vector2f(minx - x, mybot - y)))
						if (mx < abs(x) && y < my){
							mx = abs(x);
							my = y;
							atm = sf::Vector2f(-x, -y);
						}
				}

			}
		}

		//checking for out of bounds
		if(!((atm.y + _lastPos.y) < Game::SCREEN_HEIGHT) 
			|| !((atm.y + _lastPos.y) >= 0)
			|| !((atm.x + _lastPos.x) < Game::SCREEN_WIDTH)
			|| !((atm.x + _lastPos.x) >= 0)) return false;

		getSprite().move(atm);
		return true;
}