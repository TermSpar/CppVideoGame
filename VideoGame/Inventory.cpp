#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "ObjectParent.h"
#include "Boundary.h"
#include "Inventory.h"

Inventory::Inventory() {
	inventoryDisplay.setSize({ 900, 80 });
	inventoryDisplay.setPosition({ 50, 850 });
	inventoryDisplay.setFillColor(sf::Color(128, 64, 0));

	selectLine.setFillColor(sf::Color::White);
	selectLine.setSize({ 40, 2 });
}

void Inventory::add(ObjectParent *obj) {
	inventoryVec.push_back(obj);
}

void Inventory::drawTo(sf::RenderWindow &window) {
	float offsetX = 5;
	window.draw(inventoryDisplay);

	// Draw each object to the inventory:
	for (ObjectParent *obj : inventoryVec) {
		obj->getImage()->setPosition({ inventoryDisplay.getPosition().x + offsetX, inventoryDisplay.getPosition().y });
		window.draw(*obj->getImage());
		offsetX += obj->getImage()->getLocalBounds().width + 15;

		// Check if an object is selected:
		if (selected != nullptr) {
			// If the current object iteration is selected highlight it:
			if (obj->getName() == selected->getName()) {
				selectLine.setPosition(obj->getPosition().x, obj->getPosition().y + 75);
				window.draw(selectLine);
			}
		}
	}
}

void Inventory::setPosition(sf::Vector2f pos) {
	inventoryDisplay.setPosition(pos);
	for (ObjectParent *obj : inventoryVec) {
		obj->getImage()->setPosition(pos);
	}
}

void Inventory::setSelected(ObjectParent *obj) {
	selected = obj;
}

ObjectParent *Inventory::getSelected() {
	return selected;
}

std::vector<ObjectParent*> Inventory::getInventory() {
	return inventoryVec;
}