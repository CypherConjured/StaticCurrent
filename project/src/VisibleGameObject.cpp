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

sf::Vector2f VisibleGameObject::getPosition() const
{
  if(_isLoaded)
  {
    return _sprite.getPosition();
  }
  return sf::Vector2f();
}

void VisibleGameObject::setPosition(float x, float y)
{
  if(_isLoaded)
  {
    _sprite.setPosition(x,y);
  }
}

void VisibleGameObject::setPosition(sf::Vector2f vec)
{
  if(_isLoaded)
  {
    _sprite.setPosition(vec);
  }
}

void VisibleGameObject::update(float elapsedTime){ }

sf::Sprite& VisibleGameObject::getSprite()
{
  return _sprite;
}

bool VisibleGameObject::isLoaded() const
{
  return _isLoaded;
}


float VisibleGameObject::getHeight() const
{
  return _sprite.getLocalBounds().height;
}

float VisibleGameObject::getWidth() const
{
  return _sprite.getLocalBounds().width;
}


sf::Rect<float> VisibleGameObject::getBoundingRect() const
{
	return _sprite.getGlobalBounds();
}