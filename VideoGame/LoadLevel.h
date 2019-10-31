#pragma once

#include <iostream>

#include "Player.h"
#include "Boundary.h"
#include "EasyEnemy.h"

#include <fstream>
#include <string>
#include <windows.h>

#include "OpenFileDialog.h"
#include "LoadHandler.h"

#include <vector>

class LoadLevel {
public:
	LoadLevel();

	void loadLevel(Player &p);
	void runLevel(sf::RenderWindow &window, Player &player);
private:
	// File stuff:
	std::string fileName;
	std::vector<std::string> split(std::string, char);
	OpenFileDialog openFile;
	LoadHandler loadHandler;

	// Object vectors:
	std::vector<Boundary*> boundVec;
	std::vector<EasyEnemy*> easyEnemyVec;

	// Object textures:
	sf::Texture boundTexture;
	sf::Texture easyEnemyTexture;

	// Game related:
	float angle;
	float enemySpeed;

	// Level boundaries:
	float upper;
	float lower;
	float right;
	float left;
};