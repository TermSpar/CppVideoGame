#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button();

	Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);

	void setText(std::string);

	void setSize(sf::Vector2f);

	void setCharSize(int);

	void setFont(sf::Font &fonts);

	void setBackColor(sf::Color color);

	void setTextColor(sf::Color color);

	void setPosition(sf::Vector2f point);

	void drawTo(sf::RenderWindow &window);

	// Check if the mouse is within the bounds of the button:
	bool isMouseOver(sf::RenderWindow &window);
private:
	sf::RectangleShape button;
	sf::Text text;

	float btnWidth;
	float btnHeight;
};