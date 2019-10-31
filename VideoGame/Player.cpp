#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Player.h"

Player::Player() {
	health = 100;
	healthbar = new Healthbar(100);
	healthbar->setPosition({ player.getGlobalBounds().left + 5, player.getGlobalBounds().top + 60 });
}

void Player::setSprite(std::string dir) {
	// Load and set texture:
	if (!pTexture.loadFromFile(dir)) {
		std::cerr << "Error\n";
	}
	player.setTexture(pTexture);
}

void Player::move(sf::Vector2f dist) {
	if (!permStop) {
		player.move(dist);

		// Get moving direction of player:
		moveX = dist.x;
		moveY = dist.y;

		// Make name tag follow the player:
		nameTag.setPosition({ player.getGlobalBounds().left + 5, player.getGlobalBounds().top - 15 });

		// Make healthbar follow player:
		healthbar->setPosition({ player.getGlobalBounds().left + 5, player.getGlobalBounds().top + 60 });
	}
}

void Player::stop() {
	// Reverse player's movement:
	player.move({ -moveX, -moveY });
}

void Player::permanentStop(bool ToF) {
	permStop = ToF;
}

void Player::setPosition(sf::Vector2f pos) {
	player.setPosition(pos);
}

void Player::setName(std::string name, sf::Font &font) {
	// Create name tag:
	nameTag.setCharacterSize(15);
	nameTag.setFont(font);
	nameTag.setColor(sf::Color::Black);
	nameTag.setPosition({ player.getGlobalBounds().left - 5, player.getGlobalBounds().top - 17 });
	nameTag.setString(name);

	hasName = true;
}

bool Player::intersects(sf::FloatRect bounds) {
	// Check bounds intersection:
	if (player.getGlobalBounds().intersects(bounds)) {
		return true;
	}
	return false;
}

sf::FloatRect Player::getGlobalBounds() {
	return player.getGlobalBounds();
}

sf::Vector2f Player::getPosition() {
	return player.getPosition();
}

float Player::getMoveX() {
	return moveX;
}

float Player::getMoveY() {
	return moveY;
}

void Player::changeHealth(float h) {
	health += h;
	healthbar->changeHealth(h);
}

float Player::getHealth() {
	return health;
}

void Player::setAttacking(bool ToF) {
	isAttacking = ToF;
}

bool Player::getAttacking() {
	return isAttacking;
}

void Player::setButton(bool ToF) {
	isButton = ToF;
}

bool Player::isMouseOver(sf::RenderWindow &window) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = player.getPosition().x;
	int btnPosY = player.getPosition().y;

	int btnxPosWidth = player.getPosition().x + player.getGlobalBounds().width;
	int btnyPosHeight = player.getPosition().y + player.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
		return true;
	}
	return false;
}

void Player::drawTo(sf::RenderWindow &window) {
	window.draw(player);
	if (hasName) {
		window.draw(nameTag);
	}
	if (!isButton) {
		healthbar->drawTo(window);
	}
}