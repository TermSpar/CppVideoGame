#include "LoadHandler.h"


LoadHandler::LoadHandler() {

}

void LoadHandler::loadFile(std::ifstream &levelFile, Player &player, std::vector<Boundary*> &boundVec, 
	sf::Texture &boundTexture, std::vector<EasyEnemy*> &easyEnemyVec, sf::Texture &easyTexture, 
	float &upper, float &lower, float &right, float &left) {

	std::string line;

	// Line counter:
	int lineNum = 1;
	if (levelFile.is_open()) {
		while (std::getline(levelFile, line)) {
			// First line contains the player's location:
			if (lineNum == 1) {
				float xPos = stoi(split(line, ',')[0]);
				float yPos = stoi(split(line, ',')[1]);
				player.setPosition({ xPos, yPos });
			}
			// Second line contains the boundary locations:
			else if (lineNum == 2) {
				// Count number of boundaries:
				int boundCount = 0;
				for (char c : line) {
					if (c == ',') {
						boundCount++;
					}
				}
				// Create boundary at each location:
				int j = 0;
				for (int i = 0; i < boundCount; i += 2) {
					float xPos = stoi(split(line, ',')[i]);
					float yPos = stoi(split(line, ',')[i + 1]);
					boundVec.push_back(new Boundary(true));
					boundVec[j]->setPosition({ xPos, yPos });
					boundVec[j++]->setTexture(boundTexture);
				}
			}
			// Third line contains the easy enemy locations:
			else if (lineNum == 3) {
				// Count number of enemies:
				int easyEnemyCount = 0;
				for (char c : line) {
					if (c == ',') {
						easyEnemyCount++;
					}
				}
				// Create enemy at each location:
				int j = 0;
				for (int i = 0; i < easyEnemyCount; i += 2) {
					float xPos = stoi(split(line, ',')[i]);
					float yPos = stoi(split(line, ',')[i + 1]);
					easyEnemyVec.push_back(new EasyEnemy());
					easyEnemyVec[j]->setPosition({ xPos, yPos });
					easyEnemyVec[j]->setRange(200);
					easyEnemyVec[j++]->setTexture(easyTexture);
				}
			}
			// Fourth line contains level boundary locations:
			// Order: upper, lower, right, left
			else if (lineNum == 4) {
				for (int i = 0; i < 8; i += 2) {
					// Upper:
					if (i == 0) {
						upper = stoi(split(line, ',')[i + 1]);
					}
					// Lower:
					else if (i == 2) {
						lower = stoi(split(line, ',')[i + 1]);
					}
					// Right:
					else if (i == 4) {
						right = stoi(split(line, ',')[i]);
					}
					// Left:
					else if (i == 6) {
						left = stoi(split(line, ',')[i]);
					}
				}
			}
			lineNum++;
		}
		levelFile.close();
	}
}

LoadHandler::~LoadHandler() {

}

//Split String Method:
std::vector<std::string> LoadHandler::split(std::string str, char breakOn) {
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
