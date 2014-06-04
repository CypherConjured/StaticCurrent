#pragma once
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow & window);
	virtual void update(float elapsedTime);

	virtual void setPosition(float x, float y);
	virtual void setPosition(sf::Vector2f vec);

	virtual sf::Vector2f getPosition() const;
	virtual float getWidth() const;
	virtual float getHeight() const;

	virtual sf::Rect<float> getBoundingRect() const;

	virtual bool isLoaded() const;
	virtual bool isHostle(){ return _hostle; }
	virtual void setHostle(bool hos){ _hostle = hos; }

protected:
	sf::Sprite& getSprite();

private:
	sf::Sprite  _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
	bool _hostle;
};