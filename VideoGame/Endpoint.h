#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Endpoint {
public:
	Endpoint();

	sf::Sprite* getImage();

	sf::FloatRect getGlobalBounds();

	void setTexture(sf::Texture &texture);

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void drawTo(sf::RenderWindow &window);

	~Endpoint();

private:
	sf::Sprite endpoint;
};

