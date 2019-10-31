#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "ObjectParent.h"

#include "Boundary.h"

Boundary::Boundary() {
	// Load and set texture:
	if (!bTexture.loadFromFile("resources/tree.png")) {
		//std::cerr << "Error\n";
	}
	boundary.setTexture(bTexture);
}

Boundary::Boundary(bool weird) {

}

void Boundary::setTexture(sf::Texture &t) {
	boundary.setTexture(t);
}

void Boundary::setPosition(sf::Vector2f pos) {
	boundary.setPosition(pos);
}

sf::FloatRect Boundary::getGlobalBounds() {
	return boundary.getGlobalBounds();
}

sf::Vector2f Boundary::getPosition() {
	return boundary.getPosition();
}

bool Boundary::intersects(sf::FloatRect bounds) {
	// Check bounds intersection:
	if (boundary.getGlobalBounds().intersects(bounds)) {
		return true;
	}
	return false;
}

void Boundary::drawTo(sf::RenderWindow &window) {
	window.draw(boundary);
}

float Boundary::getWidth() {
	return boundary.getLocalBounds().width;
}

float Boundary::getHeight() {
	return boundary.getLocalBounds().height;
}

bool Boundary::isMouseOver(sf::RenderWindow &window) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = boundary.getPosition().x;
	int btnPosY = boundary.getPosition().y;

	int btnxPosWidth = boundary.getPosition().x + boundary.getGlobalBounds().width;
	int btnyPosHeight = boundary.getPosition().y + boundary.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
		return true;
	}
	return false;
}