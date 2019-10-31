#pragma once

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
#include "Healthpack.h"
#include "Endpoint.h"
#include "Transitions.h"

class Level1 {
public:
	Level1();

	// Only call this ONCE:
	void loadLevel();

	void runLevel(sf::RenderWindow &window, Player &player, Inventory &inv, sf::View &view, 
		int SCR_WIDTH, int SCR_HEIGHT, int &levelState);

	void setLoaded(bool set);

	bool isLoaded();

private:
	bool levelLoaded;
	bool levelCompleted;

	// Boundaries:
	std::vector<Boundary*> boundVec;

	// Weapons:
	sf::Texture swordTexture;
	Sword sword;
	sf::Texture axeTexture;
	Axe axe;

	// Enemies:
	sf::Texture enemyTexture;
	std::vector<EnemyParent*> enemyVec;
	float enemySpeed;
	float angle;

	// Healthpacks:
	sf::Texture hPackTexture;
	std::vector<Healthpack*> hPackVec;
	int hPackRegen;

	//Endpoints:
	sf::Texture endpointTexture;
	Endpoint endpoint;

	// View:
	sf::Vector2f viewPosition;

	// Transitions:
	Transitions fadeEffect;

	// Background images:
	sf::Texture bgTexture;
	sf::Sprite bgImage1;
	sf::Sprite bgImage2;
	sf::Sprite bgImage3;
	sf::Sprite bgImage4;
	sf::Sprite bgImage5;
	sf::Sprite bgImage6;
};