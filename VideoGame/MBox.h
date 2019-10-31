#pragma once
 
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Button.h"

class MBox {
public:
	MBox(sf::Font &font);
	void show(std::string msg, std::string name);
private:
	sf::RenderWindow window;
	sf::Font *btnFont;

	int sizeX;
	int sizeY;

	sf::Text message;
};