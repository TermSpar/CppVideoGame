#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class Healthbar {
public:
	Healthbar(float h);

	void setPosition(sf::Vector2f pos);

	void changeHealth(float val);

	void drawTo(sf::RenderWindow &window);
private:
	sf::RectangleShape background;
	sf::RectangleShape healthBar;
	float totalHealth;
	float currentHealth;
	float height = 10;
};