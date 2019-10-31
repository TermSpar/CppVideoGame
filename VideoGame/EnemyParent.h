#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"

class EnemyParent {
public:
	EnemyParent() { }

	virtual void setPosition(sf::Vector2f) {  }

	virtual void setTexture(sf::Texture &texture) {  }

	virtual sf::Vector2f getPosition() { sf::Vector2f v; return v; }

	virtual sf::FloatRect getGlobalBounds() { sf::FloatRect f; return f; }

	virtual bool inRange(Player &player) { return false; }

	virtual void setRange(float range) {  }

	virtual void move(sf::Vector2f) {  }

	virtual void moveRandom(int xLower, int xUpper, int yLower, int yUpper) {  }

	virtual void stop() {  }

	virtual void drawTo(sf::RenderWindow &window) {  }

	virtual void setIsDead(bool ToF) {   }

	virtual bool hasDied() { return false; }

	virtual bool isMouseOver(sf::RenderWindow &w) { return false; }

private:

};