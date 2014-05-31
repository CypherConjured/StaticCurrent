#include "stdafx.h"
#include "VisibleGameObject.h"


VisibleGameObject::VisibleGameObject() : _isLoaded(false) { }


VisibleGameObject::~VisibleGameObject(){ }

void VisibleGameObject::load(std::string filename)
{
  if(_image.loadFromFile(filename) == false)
  {
    _filename = "";
    _isLoaded = false;
  }
  else
  {
    _filename = filename;
	_sprite.setTexture(_image);
    _isLoaded = true;
  }
}

void VisibleGameObject::draw(sf::RenderWindow & renderWindow)
{
  if(_isLoaded)
  {
    renderWindow.draw(_sprite);
  }
}


void VisibleGameObject::setPosition(float x, float y)
{
  if(_isLoaded)
  {
    _sprite.setPosition(x,y);
  }
}

sf::Vector2f VisibleGameObject::getPosition() const
{
  if(_isLoaded)
  {
    return _sprite.getPosition();
  }
  return sf::Vector2f();
}

void VisibleGameObject::update(float elapsedTime)
{
}

sf::Sprite& VisibleGameObject::getSprite()
{
  return _sprite;
}

bool VisibleGameObject::isLoaded() const
{
  return _isLoaded;
}