#include <iostream>
#include <SFML/Graphics.hpp>

#include "ObjectParent.h"

#include "Sword.h"

Sword::Sword() {
	pickedUp = false;
}

sf::Sprite* Sword::getImage() {
	return &sword;
}

std::string Sword::getName() {
	return "Sword";
}

sf::FloatRect Sword::getGlobalBounds() {
	return sword.getGlobalBounds();
}

bool Sword::isPickedUp() {
	return pickedUp;
}

void Sword::setPickedUp(bool pick) {
	pickedUp = pick;
}

void Sword::setTexture(sf::Texture &texture) {
	sword.setTexture(texture);
}

void Sword::setPosition(sf::Vector2f pos) {
	sword.setPosition(pos);
}

sf::Vector2f Sword::getPosition() {
	return sword.getPosition();
}