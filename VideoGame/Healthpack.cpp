#include "Healthpack.h"



Healthpack::Healthpack() {
	pickedUp = false;
}

sf::Sprite* Healthpack::getImage() {
	return &healthpack;
}

std::string Healthpack::getName() {
	return "Sword";
}

sf::FloatRect Healthpack::getGlobalBounds() {
	return healthpack.getGlobalBounds();
}

bool Healthpack::isPickedUp() {
	return pickedUp;
}

void Healthpack::setPickedUp(bool pick) {
	pickedUp = pick;
}

void Healthpack::setTexture(sf::Texture &texture) {
	healthpack.setTexture(texture);
}

void Healthpack::setPosition(sf::Vector2f pos) {
	healthpack.setPosition(pos);
}

sf::Vector2f Healthpack::getPosition() {
	return healthpack.getPosition();
}

Healthpack::~Healthpack() {
}
