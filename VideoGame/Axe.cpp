#include <iostream>
#include <SFML/Graphics.hpp>

#include "ObjectParent.h"

#include "Axe.h"

Axe::Axe() {
	pickedUp = false;
}

sf::Sprite* Axe::getImage() {
	return &axe;
}

std::string Axe::getName() {
	return "Axe";
}

sf::FloatRect Axe::getGlobalBounds() {
	return axe.getGlobalBounds();
}

bool Axe::isPickedUp() {
	return pickedUp;
}

void Axe::setPickedUp(bool pick) {
	pickedUp = pick;
}

void Axe::setTexture(sf::Texture &texture) {
	axe.setTexture(texture);
}

void Axe::setPosition(sf::Vector2f pos) {
	axe.setPosition(pos);
}

sf::Vector2f Axe::getPosition() {
	return axe.getPosition();
}