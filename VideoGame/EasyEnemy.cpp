#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>

#include "EnemyParent.h"
#include "EasyEnemy.h"


EasyEnemy::EasyEnemy() {
	range = 10;
	moveSpeed = 0.1;
}

void EasyEnemy::setPosition(sf::Vector2f pos) {
	enemy.setPosition(pos);
}

void EasyEnemy::setTexture(sf::Texture &texture) {
	enemy.setTexture(texture);
}

sf::Vector2f EasyEnemy::getPosition() {
	return enemy.getPosition();
}

sf::FloatRect EasyEnemy::getGlobalBounds() {
	return enemy.getGlobalBounds();
}

bool EasyEnemy::inRange(Player &player) {
	if (player.getPosition().x >= enemy.getPosition().x - enemy.getGlobalBounds().width - range &&
		player.getPosition().x <= enemy.getPosition().x + range && player.getPosition().y >= enemy.getPosition().y - enemy.getGlobalBounds().height - range
		&& player.getPosition().y <= enemy.getPosition().y + range) {
		return true;
	}
	return false;
}

void EasyEnemy::setRange(float r) {
	range = r;
}

void EasyEnemy::move(sf::Vector2f dist) {
	enemy.move(dist);
	moveX = dist.x;
	moveY = dist.y;
}

void EasyEnemy::moveRandom(int xLower, int xUpper, int yLower, int yUpper) {
	// Move the enemy to a random position:
	if (!(round(enemy.getPosition().x) == rndX && round(enemy.getPosition().y) == rndY)) {

		angle = atan2(rndY - enemy.getPosition().y, rndX - enemy.getPosition().x);
		enemy.move({ cos(angle) * moveSpeed, sin(angle) * moveSpeed });
	}
	else {
		rndX = rand() % xUpper + xLower;
		rndY = rand() % yUpper + yLower;
	}
}

void EasyEnemy::stop() {
	enemy.move({ -moveX + 10, -moveY + 10 });
}

void EasyEnemy::setIsDead(bool ToF) {
	dead = ToF;
}

bool EasyEnemy::hasDied() {
	return dead;
}

bool EasyEnemy::isMouseOver(sf::RenderWindow &window) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = enemy.getPosition().x;
	int btnPosY = enemy.getPosition().y;

	int btnxPosWidth = enemy.getPosition().x + enemy.getGlobalBounds().width;
	int btnyPosHeight = enemy.getPosition().y + enemy.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
		return true;
	}
	return false;
}

void EasyEnemy::drawTo(sf::RenderWindow &window) {
	window.draw(enemy);
}