#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ObjectParent.h"

class Healthpack : public ObjectParent {
public:
	Healthpack();

	virtual sf::Sprite* getImage();

	virtual std::string getName();

	virtual sf::FloatRect getGlobalBounds();

	virtual bool isPickedUp();

	virtual void setPickedUp(bool pick);

	virtual void setTexture(sf::Texture &texture);

	virtual void setPosition(sf::Vector2f pos);

	virtual sf::Vector2f getPosition();

	~Healthpack();
private:
	sf::Sprite healthpack;
	std::string name;
	bool pickedUp;
};

