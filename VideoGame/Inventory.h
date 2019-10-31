#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ObjectParent.h"
#include "Boundary.h"

class Inventory {
public:
	Inventory();

	void add(ObjectParent *obj);

	void drawTo(sf::RenderWindow &window);

	void setPosition(sf::Vector2f pos);

	void setSelected(ObjectParent *obj);

	ObjectParent *getSelected();

	std::vector<ObjectParent*> getInventory();
private:
	sf::RectangleShape inventoryDisplay;
	sf::RectangleShape selectLine;
	std::vector<ObjectParent*> inventoryVec;
	ObjectParent *selected;
};