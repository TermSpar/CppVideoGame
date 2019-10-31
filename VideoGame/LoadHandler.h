#pragma once

#include <iostream>

#include "Player.h"
#include "Boundary.h"
#include "EasyEnemy.h"

#include <fstream>
#include <string>
#include <vector>

class LoadHandler {
public:
	LoadHandler();
	void loadFile(std::ifstream &file, Player &player, std::vector<Boundary*> &boundVec, sf::Texture &boundTexture, 
		std::vector<EasyEnemy*> &easyEnemyVec, sf::Texture &easyTexture, float &upper, float &lower, float &right, float &left);
	~LoadHandler();
private:
	std::vector<std::string> split(std::string, char);
};

