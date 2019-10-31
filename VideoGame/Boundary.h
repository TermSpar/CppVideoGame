#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "ObjectParent.h"

class Boundary {
public:
	Boundary();

	Boundary(bool);

	void setPosition(sf::Vector2f pos);

	sf::FloatRect getGlobalBounds();

	sf::Vector2f getPosition();

	bool intersects(sf::FloatRect bounds);

	void setTexture(sf::Texture &t);

	void drawTo(sf::RenderWindow &window);

	float getWidth();

	float getHeight();

	bool isMouseOver(sf::RenderWindow &w);
private:
	sf::Texture bTexture;
	sf::Sprite boundary;
};