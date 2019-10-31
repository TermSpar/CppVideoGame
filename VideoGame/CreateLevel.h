#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Boundary.h"
#include "EasyEnemy.h"

#include "Button.h"
#include "SaveFileDialog.h"
#include "OpenFileDialog.h"
#include "LoadHandler.h"

#include "MBox.h"

#include <sstream>

#define NOTHING -1
#define BOUND 0
#define EASY_ENEMY 1
#define PLAYER 2

#define LEFT_BOUND 3
#define RIGHT_BOUND 4
#define UPPER_BOUND 5
#define LOWER_BOUND 6

class CreateLevel {
public:
	CreateLevel(sf::Font &f);
	void createLevel(sf::RenderWindow &window, sf::View &v);
	void inputEvents(std::string, std::string key, sf::RenderWindow &w);
	~CreateLevel();
private:
	// GUI stuff:
	bool isLoaded;

	// Container:
	sf::RectangleShape selectionBox;

	// btnSave:
	Button *btnSave;
	void saveAll();
	SaveFileDialog saveFile;
	std::ostringstream dataStream;
	std::string data;

	// btnOpen
	Button *btnOpen;

	// Load file data:
	void openProject();
	OpenFileDialog openFile;
	std::string fileName;
	LoadHandler loadHandler;

	// Textures:
	sf::Texture boundTexture;
	sf::Texture easyEnemyTexture;

	// Player stuff:
	Player player;
	bool playerHasMoved = false;

	// Boundary stuff:
	Boundary btnBoundary;
	std::vector<Boundary*> boundVec;

	int boundCount = 0;
	int selectedBound = -1;

	// EasyEnemy stuff:
	EasyEnemy btnEasyEnemy;
	std::vector<EasyEnemy*> easyEnemyVec;

	int easyEnemyCount = 0;
	int selectedEasyEnemy = -1;

	// Level boundaries:
	sf::Text upperBound;
	sf::Text lowerBound;
	sf::Text rightBound;
	sf::Text leftBound;

	// Drag stuff:
	int isPressed = NOTHING;

	// View:
	float viewX;
	float viewY;

	// isMouseOver:
	bool isMouseOver(sf::RenderWindow &w, sf::Text &t);

	// Level boundaries:
	float upper;
	float lower;
	float right;
	float left;
};
