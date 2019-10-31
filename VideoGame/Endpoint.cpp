#include "Endpoint.h"

#include <iostream>
#include <SFML/Graphics.hpp>

Endpoint::Endpoint() {
}


sf::Sprite* Endpoint::getImage() {
	return &endpoint;
}

sf::FloatRect Endpoint::getGlobalBounds() {
	return endpoint.getGlobalBounds();
}

void Endpoint::setTexture(sf::Texture &texture) {
	endpoint.setTexture(texture);
}

void Endpoint::setPosition(sf::Vector2f pos) {
	endpoint.setPosition(pos);
}

sf::Vector2f Endpoint::getPosition() {
	return endpoint.getPosition();
}

void Endpoint::drawTo(sf::RenderWindow &window) {
	window.draw(endpoint);
}

Endpoint::~Endpoint() {
}
