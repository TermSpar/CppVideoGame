#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "Player.h"
#include "Boundary.h"
#include "Axe.h"
#include "Sword.h"
#include "EasyEnemy.h"
#include "Inventory.h"
#include "Healthpack.h"
#include "Endpoint.h"

#include "Level1.h"

Level1::Level1() {
	levelLoaded = false;
	enemySpeed = 0.7;
}

// Only call this ONCE:
void Level1::loadLevel() {
	// Instantiate boundaries:
	float xPos = 10;
	float yPos = 300;
	for (int i = 0; i < 10; i++) {
		Boundary *temp = new Boundary();
		boundVec.push_back(temp);
		boundVec[i]->setPosition({ xPos, 300 });
		xPos += boundVec[i]->getWidth();
	}
	for (int i = 10; i < 20; i++) {
		Boundary *temp = new Boundary();
		boundVec.push_back(temp);
		boundVec[i]->setPosition({ 10, yPos });
		yPos += boundVec[i]->getHeight();
	}

	// Objects:
	swordTexture.loadFromFile("resources/sword.png");
	sword.setTexture(swordTexture);
	sword.setPosition({ 200, 200 });

	axeTexture.loadFromFile("resources/axe.png");
	axe.setTexture(axeTexture);
	axe.setPosition({ 400,400 });

	// Enemies:
	enemyTexture.loadFromFile("resources/enemy.png");
	float loc = 200;
	for (int i = 0; i < 3; i++) {
		enemyVec.push_back(new EasyEnemy());
		enemyVec[i]->setTexture(enemyTexture);
		enemyVec[i]->setPosition({ 700, loc });
		enemyVec[i]->setRange(200);
		loc += 100;
	}

	// Healthpacks:
	hPackRegen = 10;
	hPackTexture.loadFromFile("resources/healthpack.png");
	for (int i = 0; i < 3; i++) {
		hPackVec.push_back(new Healthpack());
		hPackVec[i]->setTexture(hPackTexture);
	}
	hPackVec[0]->setPosition({ 600, 900 });
	hPackVec[1]->setPosition({ 700, 800 });
	hPackVec[2]->setPosition({ 800, 1000 });

	//Endpoints:
	endpointTexture.loadFromFile("resources/endpoint.png");
	endpoint.setTexture(endpointTexture);
	endpoint.setPosition({ 1780, 1600 });

	// Background images:
	bgTexture.loadFromFile("resources/grass.png");

	bgImage1.setTexture(bgTexture);
	bgImage1.setPosition({ 0, 0 });

	bgImage2.setTexture(bgTexture);
	bgImage2.setPosition({ bgImage1.getLocalBounds().width, 0 });

	bgImage3.setTexture(bgTexture);
	bgImage3.setPosition({ -bgImage1.getLocalBounds().width, 0 });

	bgImage4.setTexture(bgTexture);
	bgImage4.setPosition({ 0, bgImage1.getLocalBounds().height });

	bgImage5.setTexture(bgTexture);
	bgImage5.setPosition({ bgImage4.getLocalBounds().width, bgImage1.getLocalBounds().height });

	bgImage6.setTexture(bgTexture);
	bgImage6.setPosition({ -bgImage4.getLocalBounds().width, bgImage1.getLocalBounds().height });
}

void Level1::runLevel(sf::RenderWindow &window, Player &player, Inventory &inv, sf::View &view, 
	int SCR_WIDTH, int SCR_HEIGHT, int &levelState) {
	// Draw background images:
	window.draw(bgImage1);
	window.draw(bgImage2);
	window.draw(bgImage3);
	window.draw(bgImage4);
	window.draw(bgImage5);
	window.draw(bgImage6);

	// Center view on player within bounds:
	if (player.getPosition().x + 16 > SCR_WIDTH / 2)
		viewPosition.x = player.getPosition().x + 16;
	else
		viewPosition.x = SCR_WIDTH / 2;

	if (player.getPosition().x + 16 > SCR_WIDTH + 550)
		viewPosition.x = SCR_WIDTH + 550;

	if (player.getPosition().y + 16 > SCR_HEIGHT / 2)
		viewPosition.y = player.getPosition().y + 16;
	else
		viewPosition.y = SCR_HEIGHT / 2;

	if (player.getPosition().y + 16 > SCR_HEIGHT + 550)
		viewPosition.y = SCR_HEIGHT + 550;

	view.setCenter(viewPosition);

	// Keep player within bounds of level:
	if (player.getPosition().x >= 1830 || player.getPosition().x < 0 || player.getPosition().y < 0
		|| player.getPosition().y > 1765) {
		player.stop();
	}

	// Draw boundaries and check collisions:
	for (Boundary *b : boundVec) {
		b->drawTo(window);
		if (player.intersects(b->getGlobalBounds())) {
			player.stop();
		}
	}

	// Draw sword and check collisions:
	if (!sword.isPickedUp()) {
		window.draw(*sword.getImage());
	}
	if (player.intersects(sword.getGlobalBounds()) && !sword.isPickedUp()) {
		sword.setPickedUp(true);
		inv.add(&sword);
	}

	// Draw axe and check collisions:
	if (!axe.isPickedUp()) {
		window.draw(*axe.getImage());
	}
	if (player.intersects(axe.getGlobalBounds()) && !axe.isPickedUp()) {
		axe.setPickedUp(true);
		inv.add(&axe);
	}

	// Draw healthpacks and check collisions:
	for (Healthpack *hPack : hPackVec) {
		if (!hPack->isPickedUp()) {
			window.draw(*hPack->getImage());
		}
		if (player.intersects(hPack->getGlobalBounds())) {
			// Increase health by specified amount:
			hPack->setPickedUp(true);
			hPack->setPosition({ 109324, 423342 });
			player.changeHealth(hPackRegen);
		}
	}

	//Draw endpoint and check collision:
	endpoint.drawTo(window);
	// When the player has finished the level:
	if (player.intersects(endpoint.getGlobalBounds())) {
		// Clear all current level data:
		enemyVec.clear();
		boundVec.clear();
		hPackVec.clear();

		fadeEffect.fadeEffect(window);
		//player.permanentStop(true);

		// Move on to next level:
		levelState++;
	}

	// Draw enemies and make them wander:
	for (EnemyParent *enemy : enemyVec) {
		if(!enemy->hasDied())
			enemy->drawTo(window);
		// If the enemies see the player, follow him:
		if (enemy->inRange(player)) {
			angle = atan2(player.getPosition().y - enemy->getPosition().y, player.getPosition().x - enemy->getPosition().x);
			enemy->move({ cos(angle) * enemySpeed, sin(angle) * enemySpeed });
		}
		else {
			enemy->moveRandom(100, 600, 50, 500);
		}

		// Allow player to attack enemy:
		if (player.getAttacking()) {
			// If player is attacking with sword:
			if (inv.getSelected() != nullptr) {
				if (inv.getSelected()->getName() == "Sword" || inv.getSelected()->getName() == "Axe") {
					if (player.intersects(enemy->getGlobalBounds())) {
						enemy->setIsDead(true);
					}
				}
			}
		}

		// Enemy-player collisions:
		if (player.intersects(enemy->getGlobalBounds()) && !enemy->hasDied()) {
			player.changeHealth(-10);
			enemy->move({ 300, 300 });
		}
	}
}

void Level1::setLoaded(bool set) {
	levelLoaded = set;
}

bool Level1::isLoaded() {
	return levelLoaded;
}