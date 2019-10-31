#pragma once

// Parent class for all usable objects:

class ObjectParent {
public:
	virtual sf::Sprite* getImage() { sf::Sprite s; return &s; }

	virtual std::string getName() { return ""; }

	virtual void setPosition(sf::Vector2f) {  }

	virtual sf::FloatRect getGlobalBounds() { sf::FloatRect f; return f; }

	virtual bool isPickedUp() { return false; }

	virtual void setPickedUp(bool) {  }

	virtual sf::Vector2f getPosition() { sf::Vector2f v; return v; }
};