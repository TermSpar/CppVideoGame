#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>

#include "EnemyParent.h"

class EasyEnemy : public EnemyParent {
public:
	EasyEnemy();

	virtual void setPosition(sf::Vector2f pos);

	virtual void setTexture(sf::Texture &texture);

	virtual sf::Vector2f getPosition();

	virtual sf::FloatRect getGlobalBounds();

	virtual bool inRange(Player &player);

	virtual void setRange(float r);

	virtual void move(sf::Vector2f dist);

	virtual void moveRandom(int xLower, int xUpper, int yLower, int yUpper);

	virtual void stop();

	virtual void setIsDead(bool ToF);

	virtual bool hasDied();

	virtual void drawTo(sf::RenderWindow &window);

	virtual bool isMouseOver(sf::RenderWindow &w);
private:
	sf::Sprite enemy;
	float range;
	float angle;
	float moveSpeed;
	float rndX = 500;
	float rndY = 300;
	bool dead = false;

	float moveX;
	float moveY;
};