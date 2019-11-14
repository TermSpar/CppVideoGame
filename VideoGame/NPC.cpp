#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>

#include "NPC.h"


NPC::NPC() {
	range = 10;
	moveSpeed = 0.1;
}

void NPC::setPosition(sf::Vector2f pos) {
	npc.setPosition(pos);
}

void NPC::setTexture(sf::Texture &texture) {
	npc.setTexture(texture);
}

sf::Vector2f NPC::getPosition() {
	return npc.getPosition();
}

sf::FloatRect NPC::getGlobalBounds() {
	return npc.getGlobalBounds();
}

bool NPC::inRange(Player &player) {
	if (player.getPosition().x >= npc.getPosition().x - npc.getGlobalBounds().width - range &&
		player.getPosition().x <= npc.getPosition().x + range && player.getPosition().y >= npc.getPosition().y - npc.getGlobalBounds().height - range
		&& player.getPosition().y <= npc.getPosition().y + range) {
		return true;
	}
	return false;
}

void NPC::setRange(float r) {
	range = r;
}

void NPC::move(sf::Vector2f dist) {
	npc.move(dist);
	moveX = dist.x;
	moveY = dist.y;
}

void NPC::moveRandom(int xLower, int xUpper, int yLower, int yUpper) {
	// Move the NPC to a random position:
	if (!(round(npc.getPosition().x) == rndX && round(npc.getPosition().y) == rndY)) {

		angle = atan2(rndY - npc.getPosition().y, rndX - npc.getPosition().x);
		npc.move({ cos(angle) * moveSpeed, sin(angle) * moveSpeed });
	}
	else {
		rndX = rand() % xUpper + xLower;
		rndY = rand() % yUpper + yLower;
	}
}

void NPC::stop() {
	npc.move({ -moveX + 10, -moveY + 10 });
}

void NPC::setIsDead(bool ToF) {
	dead = ToF;
}

bool NPC::hasDied() {
	return dead;
}

bool NPC::isMouseOver(sf::RenderWindow &window) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = npc.getPosition().x;
	int btnPosY = npc.getPosition().y;

	int btnxPosWidth = npc.getPosition().x + npc.getGlobalBounds().width;
	int btnyPosHeight = npc.getPosition().y + npc.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
		return true;
	}
	return false;
}

void NPC::drawTo(sf::RenderWindow &window) {
	window.draw(npc);
}