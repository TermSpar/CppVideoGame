#include <iostream>
#include <SFML/Graphics.hpp>

#include "Button.h"

Button::Button() {

}

Button::Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
	button.setSize(buttonSize);
	button.setFillColor(bgColor);

	// Get these for later use:
	btnWidth = buttonSize.x;
	btnHeight = buttonSize.y;

	text.setString(btnText);
	text.setCharacterSize(charSize);
	text.setColor(textColor);
}

void Button::setText(std::string t) {
	text.setString(t);
}

void Button::setSize(sf::Vector2f s) {
	button.setSize(s);
}

void Button::setCharSize(int c) {
	text.setCharacterSize(c);
}

void Button::setFont(sf::Font &fonts) {
	text.setFont(fonts);
}

void Button::setBackColor(sf::Color color) {
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	text.setColor(color);
}

void Button::setPosition(sf::Vector2f point) {
	button.setPosition(point);

	// Center text on button:
	float div = 2.0 + btnHeight / btnWidth;

	float xPos = (point.x + btnWidth / div) - (text.getLocalBounds().width / 2);
	float yPos = (point.y + btnHeight / div) - (text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

void Button::drawTo(sf::RenderWindow &window) {
	window.draw(button);
	window.draw(text);
}

// Check if the mouse is within the bounds of the button:
bool Button::isMouseOver(sf::RenderWindow &window) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = button.getPosition().x;
	int btnPosY = button.getPosition().y;

	int btnxPosWidth = button.getPosition().x + button.getGlobalBounds().width;
	int btnyPosHeight = button.getPosition().y + button.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
		return true;
	}
	return false;
}