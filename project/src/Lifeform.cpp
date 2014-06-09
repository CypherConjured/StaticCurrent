#include "stdafx.h"
#include "Lifeform.h"
#include "Game.h"

Lifeform::Lifeform() : _velocity(sf::Vector2f()), _targetVelocity(sf::Vector2f(0,0)) { }
Lifeform::~Lifeform(){ }

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

    if(pos.x  < getSprite().getOrigin().x){
        _velocity.x = 0;
		setPosition(getSprite().getOrigin().x,pos.y);
    }else if(pos.x > (Game::SCREEN_WIDTH - getSprite().getOrigin().x)){
		_velocity.x = 0;
		setPosition((Game::SCREEN_WIDTH - getSprite().getOrigin().x),pos.y);
	}
    _lastPos = getPosition();

	attemptMove( dt );
    getSprite().move(sf::Vector2f(0,_velocity.y) * dt);
	_onGround = collidesGround();

	if(_onGround)
		setPosition(getPosition().x,_lastPos.y);
} 

void Lifeform::calculateVelocity(){
	float _a = .2f;
	float _threshold = .01f;

	_velocity = _a * _targetVelocity + (1-_a) * _velocity;

	if (abs(_velocity.x) < _threshold) _velocity.x = 0;
	if (abs(_velocity.y) < _threshold) _velocity.y = 0;
}


bool Lifeform::collidesGround(){
	sf::Sprite mysprite = getSprite();
	int mybot = (int)(getPosition().y + getHeight()/2);
	int minx = (int)(getPosition().x - getWidth()/2);
	int maxx = (int)(getPosition().x + getWidth()/2);
	Level* currentLevel = Game::GetLevel();

	if(currentLevel->getLevelBitmask().getPixel(minx,mybot).b < 128 || currentLevel->getLevelBitmask().getPixel(maxx,mybot).b < 128){
		return false;
	}else{
		return true;
	}
}

bool Lifeform::detectCollisionAtPoint( sf::Vector2f p ){
	Level* currentLevel = Game::GetLevel();

	if(currentLevel->getLevelBitmask().getPixel(p.x,p.y).b < 128){
		return false;
	}else{
		return true;
	}

}

void Lifeform::attemptMove( float dt ){
	int mybot = static_cast<int>(getPosition().y + getHeight()/2);
	int mytop = static_cast<int>(getPosition().y - getHeight()/2);
	int minx = static_cast<int>(getPosition().x - getWidth()/2);
	int maxx = static_cast<int>(getPosition().x + getWidth()/2);

	_lastPos = getPosition();
	float dirx = _velocity.x * dt;
	float diry = _velocity.y * dt;
	sf::Vector2f atm;
	//if( abs(dirx) > abs(diry) ){
		for( float x = 0; x <= abs(dirx); x++){
			for( float y = 0; y >= 3; y++){
				if(dirx > 0){
					if( !detectCollisionAtPoint(sf::Vector2f(maxx+x,mybot-y)) )
						atm = sf::Vector2f(x,-y);
				}else{
					if( !detectCollisionAtPoint(sf::Vector2f(minx-x,mybot-y)) )
						atm = sf::Vector2f(-x,-y);
				}

			}
		}
		/*for( float y = 0; y <= abs(diry); y++){
			if(diry > 0){
				if(dirx > 0){
					if( !detectCollisionAtPoint(sf::Vector2f(maxx,mybot+y)) )
						atm = sf::Vector2f(0,y);
				}else{
					if( !detectCollisionAtPoint(sf::Vector2f(minx,mybot+y)) )
						atm = sf::Vector2f(0,y);
				}
			}else{
				if(dirx > 0){
					if( !detectCollisionAtPoint(sf::Vector2f(maxx,mytop-y)) )
						atm = sf::Vector2f(0,-y);
				}else{
					if( !detectCollisionAtPoint(sf::Vector2f(minx,mytop-y)) )
						atm = sf::Vector2f(0,-y);
				}
			}
		}
	/*}else{
		for( float y = 0; y <= abs(diry); y++){
			if(diry > 0){
				if(dirx > 0){
					if( !detectCollisionAtPoint(sf::Vector2f(maxx,mybot+y)) )
						atm = sf::Vector2f(0,y);
				}else{
					if( !detectCollisionAtPoint(sf::Vector2f(minx,mybot+y)) )
						atm = sf::Vector2f(0,y);
				}
			}else{
				if(dirx > 0){
					if( !detectCollisionAtPoint(sf::Vector2f(maxx,mytop-y)) )
						atm = sf::Vector2f(0,-y);
				}else{
					if( !detectCollisionAtPoint(sf::Vector2f(minx,mytop-y)) )
						atm = sf::Vector2f(0,-y);
				}
			}
		}
		for( float x = 0; x <= abs(dirx); x++){
			for( float y = 0; y >= 3; y++){
				if(dirx > 0){
					if( !detectCollisionAtPoint(sf::Vector2f(maxx+x,mybot-y)) )
						atm = sf::Vector2f(x,-y);
				}else{
					if( !detectCollisionAtPoint(sf::Vector2f(minx-x,mybot-y)) )
						atm = sf::Vector2f(-x,-y);
				}

			}
		}
	}*/
	getSprite().move(atm);
}