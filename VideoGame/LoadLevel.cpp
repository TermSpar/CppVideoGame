#include "LoadLevel.h"

// Public:
LoadLevel::LoadLevel() {
	boundTexture.loadFromFile("resources/tree.png");
	easyEnemyTexture.loadFromFile("resources/enemy.png");
	enemySpeed = 0.7;
}

void LoadLevel::loadLevel(Player &player) {
	// Get file:
	openFile.openFileDialog(fileName);
	std::ifstream levelFile(fileName);

	// Load all data from the file:
	loadHandler.loadFile(levelFile, player, boundVec, boundTexture, easyEnemyVec, easyEnemyTexture, 
		upper, lower, right, left);
}

void LoadLevel::runLevel(sf::RenderWindow &window, Player &player) {
	// Draw player:
	player.drawTo(window);

	// Keep player within bounds of level:
	if (player.getPosition().x >= right || player.getPosition().x < left || player.getPosition().y < upper
		|| player.getPosition().y > lower) {
		player.stop();
	}

	// Draw boundaries and check collisions:
	for (Boundary *b : boundVec) {
		b->drawTo(window);
		if (player.intersects(b->getGlobalBounds())) {
			player.stop();
		}
	}

	// Draw enemies and make them wander:
	for (EnemyParent *enemy : easyEnemyVec) {
		if (!enemy->hasDied())
			enemy->drawTo(window);
		// If the enemies see the player, follow him:
		if (enemy->inRange(player)) {
			angle = atan2(player.getPosition().y - enemy->getPosition().y, player.getPosition().x - enemy->getPosition().x);
			enemy->move({ cos(angle) * enemySpeed, sin(angle) * enemySpeed });
		}
		else {
			enemy->moveRandom(100, 600, 50, 500);
		}

		// Enemy-player collisions:
		if (player.intersects(enemy->getGlobalBounds()) && !enemy->hasDied()) {
			player.changeHealth(-10);
			enemy->stop();
		}
	}
}

//Split String Method:
std::vector<std::string> LoadLevel::split(std::string str, char breakOn) {
	//Declare Variables:
	std::vector<std::string> sVec;
	std::string statement = "";
	str += breakOn;
	//Traverse str:
	for (unsigned int i = 0; i < str.size(); i++) {
		//If Iteration != breakOn:
		if (str.at(i) != breakOn) {
			//Add It To statement:
			statement += str.at(i);
		}
		//If Iteration == breakOn:
		else if (str.at(i) == breakOn) {
			//Push Vector With statement
			statement += str.at(i);
			sVec.push_back(statement);
			//Reset Statement:
			statement = "";
		}
	}
	//Remove Appended Char
	statement += sVec.at(1);
	statement = statement.substr(0, statement.length() - 1);
	sVec.at(1) = statement;
	//Return sVec:
	return sVec;
}