#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Transitions {
public:
	Transitions();

	void fadeEffect(sf::RenderWindow &w);

	~Transitions();

private:
	sf::RectangleShape effect;
};

