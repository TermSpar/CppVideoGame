#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "Heathbar.h"

Healthbar::Healthbar(float h) {
	background.setSize({ h, height });
	background.setFillColor(sf::Color::Black);

	healthBar.setSize({ h, height });
	healthBar.setFillColor(sf::Color::Green);

	totalHealth = currentHealth = h;
}

void Healthbar::setPosition(sf::Vector2f pos) {
	background.setPosition(pos);
	healthBar.setPosition(pos);
}

void Healthbar::changeHealth(float val) {
	float newHealth = currentHealth + val;
	// If desired health is within bounds:
	if (newHealth >= -1 && newHealth <= totalHealth) {
		currentHealth = newHealth;
		healthBar.setSize({ newHealth, height });
	}
}

void Healthbar::drawTo(sf::RenderWindow &window) {
	window.draw(background);
	window.draw(healthBar);
}