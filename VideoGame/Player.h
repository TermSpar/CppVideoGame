#pragma once

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Heathbar.h"

class Player {
public:

	Player();

	void setSprite(std::string dir);

	void move(sf::Vector2f dist);

	void stop();

	void permanentStop(bool ToF);

	void setPosition(sf::Vector2f pos);

	void setName(std::string name, sf::Font &font);

	bool intersects(sf::FloatRect bounds);

	sf::FloatRect getGlobalBounds();

	sf::Vector2f getPosition();

	float getMoveX();

	float getMoveY();

	void changeHealth(float h);

	float getHealth();

	void setAttacking(bool ToF);

	bool getAttacking();

	void drawTo(sf::RenderWindow &window);

	void setButton(bool);

	bool isMouseOver(sf::RenderWindow &w);
private:
	sf::Texture pTexture;
	sf::Sprite player;

	bool hasName = false;
	sf::Text nameTag;

	float moveX;
	float moveY;

	bool permStop = false;

	bool isAttacking = false;

	float health;
	Healthbar *healthbar;

	bool isButton = false;
};