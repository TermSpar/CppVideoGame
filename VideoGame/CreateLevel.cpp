#include <iostream>

#include "CreateLevel.h"

CreateLevel::CreateLevel(sf::Font &font) {
	// Load textures:
	boundTexture.loadFromFile("resources/tree.png");
	easyEnemyTexture.loadFromFile("resources/enemy.png");
	isLoaded = false;

	// btnSave:
	btnSave = new Button("Save & Export", { 150, 50 }, 15, sf::Color::Green, sf::Color::Black);
	btnSave->setFont(font);
	btnSave->setPosition({ 770, 1 });

	// btnOpen:
	btnOpen = new Button("Open Project", { 150, 50 }, 15, sf::Color::Cyan, sf::Color::Black);
	btnOpen->setFont(font);
	btnOpen->setPosition({ 770, 55 });

	// Level boundaries:
	int charSize = 12;
	upperBound.setCharacterSize(charSize);
	upperBound.setFont(font);
	upperBound.setColor(sf::Color::Red);
	upperBound.setString("UPPER BOUND");
	upperBound.setPosition({ 350, 50 });

	lowerBound.setCharacterSize(charSize);
	lowerBound.setFont(font);
	lowerBound.setColor(sf::Color::Red);
	lowerBound.setString("LOWER BOUND");
	lowerBound.setPosition({ 350, 760 });

	rightBound.setCharacterSize(charSize);
	rightBound.setFont(font);
	rightBound.setColor(sf::Color::Red);
	rightBound.setString("RIGHT BOUND");
	rightBound.setPosition({ 700, 400 });

	leftBound.setCharacterSize(charSize);
	leftBound.setFont(font);
	leftBound.setColor(sf::Color::Red);
	leftBound.setString("LEFT BOUND");
	leftBound.setPosition({ 100, 400 });
}

void CreateLevel::createLevel(sf::RenderWindow &window, sf::View &view) {

	// Load GUI:
	if (!isLoaded) {

		// Menu:
		selectionBox.setSize({ 900, 90 });
		selectionBox.setPosition({ 0, 810 });
		selectionBox.setFillColor(sf::Color::White);

		// btnPlayer:
		player.setSprite("resources/player.png");
		player.setButton(true);
		player.setPosition({ 10, 820 });

		// btnBoundary:
		btnBoundary.setPosition({ 110, 820 });

		// btnEasyEnemy:
		btnEasyEnemy.setTexture(easyEnemyTexture);
		btnEasyEnemy.setPosition({ 190, 825 });

		// Set view:
		view.reset(sf::FloatRect(0, 0, 900, 900));
		viewX = view.getCenter().x;
		viewY = view.getCenter().y;

		isLoaded = true;
	}

	// Once everything is loaded:

	// Draw boundaries:
	for (int i = 0; i < boundVec.size(); i++) {
		if (boundVec[i] != nullptr) {
			boundVec[i]->drawTo(window);
		}
	}

	// Draw enemies:
	for (int i = 0; i < easyEnemyVec.size(); i++) {
		if (easyEnemyVec[i] != nullptr) {
			easyEnemyVec[i]->drawTo(window);
		}
	}

	// Draw buttons:
	btnSave->drawTo(window);
	btnOpen->drawTo(window);

	window.draw(selectionBox);

	// Draw items:
	player.drawTo(window);
	btnBoundary.drawTo(window);
	btnEasyEnemy.drawTo(window);

	// Draw level boundaries:
	window.draw(upperBound);
	window.draw(lowerBound);
	window.draw(rightBound);
	window.draw(leftBound);

	// Set view:
	window.setView(view);
	view.setCenter({ viewX, viewY });

	// Have GUI follow view:
	selectionBox.setPosition({ view.getCenter().x - 900 / 2, view.getCenter().y + 900 / 4 + 145 });
	// Make sure the player has not moved:
	if (!playerHasMoved) {
		// Player follow:
		player.setPosition({ view.getCenter().x - 900 / 2 + 10, view.getCenter().y + 900 / 4 + 155 });
	}
	// btnBoundary follow:
	btnBoundary.setPosition({ view.getCenter().x - 900 / 2 + 100, view.getCenter().y + 900 / 4 + 150 });
	// btnEasyEnemy follow:
	btnEasyEnemy.setPosition({ view.getCenter().x - 900 / 2 + 180, view.getCenter().y + 900 / 4 + 160 });
	// btnSave follow:
	btnSave->setPosition({ view.getCenter().x - 900 / 2 + 750, view.getCenter().y - 447 });
	// btnOpen follow:
	btnOpen->setPosition({ view.getCenter().x - 900 / 2 + 750, view.getCenter().y - 390 });
}

void CreateLevel::inputEvents(std::string e, std::string key, sf::RenderWindow &window) {
	// Mouse events:
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });
	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	if (e == "pressed") {
		// Drag items onto screen:
		if (player.isMouseOver(window) && isPressed == NOTHING) {
			// Drag the one player:
			player.setPosition({ mouseX - 30, mouseY - 30 });
			playerHasMoved = true;
			isPressed = PLAYER;
		}
		// Drag boundaries:
		else if (btnBoundary.isMouseOver(window) && isPressed == NOTHING) {
			// Create new boundary when pressed:
			boundVec.push_back(new Boundary(true));
			boundVec[boundCount]->setTexture(boundTexture);
			selectedBound = boundCount;
			boundVec[boundCount++]->setPosition({ mouseX - 30, mouseY - 30 });
			isPressed = BOUND;
		}
		// Drag easy enemies:
		else if (btnEasyEnemy.isMouseOver(window) && isPressed == NOTHING) {
			easyEnemyVec.push_back(new EasyEnemy());
			easyEnemyVec[easyEnemyCount]->setTexture(easyEnemyTexture);
			selectedEasyEnemy = easyEnemyCount;
			easyEnemyVec[easyEnemyCount++]->setPosition({ mouseX - 30, mouseY - 30 });
			isPressed = EASY_ENEMY;
		}

		// Continue to drag player:
		if (isPressed == PLAYER) {
			player.setPosition({ mouseX - 30, mouseY - 30 });
		}

		// Drag newly created bounds:
		for (int i = 0; i < boundVec.size(); i++) {
			if (boundVec[i]->isMouseOver(window) && isPressed == NOTHING) {
				isPressed = BOUND;
				selectedBound = i;
			}
		}
		if (isPressed == BOUND) {
			boundVec[selectedBound]->setPosition({ mouseX - 30, mouseY - 30 });
		}

		// Drag newly created easy enemies:
		for (int i = 0; i < easyEnemyVec.size(); i++) {
			if (easyEnemyVec[i]->isMouseOver(window) && isPressed == NOTHING) {
				isPressed = EASY_ENEMY;
				selectedEasyEnemy = i;
			}
		}
		if (isPressed == EASY_ENEMY) {
			easyEnemyVec[selectedEasyEnemy]->setPosition({ mouseX - 30, mouseY - 30 });
		}

		// Drag level boundaries:
		if (isMouseOver(window, upperBound) && isPressed == NOTHING) {
			// Drag the one upperBound:
			upperBound.setPosition({ mouseX - 30, mouseY - 30 });
			isPressed = UPPER_BOUND;
		}

		// Continue to drag upperBound:
		if (isPressed == UPPER_BOUND) {
			upperBound.setPosition({ mouseX - 30, mouseY - 30 });
		}

		if (isMouseOver(window, lowerBound) && isPressed == NOTHING) {
			// Drag the one lowerBound:
			lowerBound.setPosition({ mouseX - 30, mouseY - 30 });
			isPressed = LOWER_BOUND;
		}

		// Continue to drag lowerBound:
		if (isPressed == LOWER_BOUND) {
			lowerBound.setPosition({ mouseX - 30, mouseY - 30 });
		}

		if (isMouseOver(window, rightBound) && isPressed == NOTHING) {
			// Drag the one rightBound:
			rightBound.setPosition({ mouseX - 30, mouseY - 30 });
			isPressed = RIGHT_BOUND;
		}

		// Continue to drag rightBiund:
		if (isPressed == RIGHT_BOUND) {
			rightBound.setPosition({ mouseX - 30, mouseY - 30 });
		}

		if (isMouseOver(window, leftBound) && isPressed == NOTHING) {
			// Drag the one leftBound:
			leftBound.setPosition({ mouseX - 30, mouseY - 30 });
			isPressed = LEFT_BOUND;
		}

		// Continue to drag leftBound:
		if (isPressed == LEFT_BOUND) {
			leftBound.setPosition({ mouseX - 30, mouseY - 30 });
		}

		// Save the level:
		if (btnSave->isMouseOver(window)) {
			saveAll();
		}
		// Open project:
		else if (btnOpen->isMouseOver(window)) {
			openProject();
		}
	}
	else if (e == "released") {
		// Release selected boundary:
		if (isPressed == BOUND) {
			if (selectedBound != -1) {
				if (boundVec[selectedBound]->isMouseOver(window)) {
					isPressed = NOTHING;
				}
			}
		}
		else if (isPressed == EASY_ENEMY) {
			if (selectedEasyEnemy != -1) {
				if (easyEnemyVec[selectedEasyEnemy]->isMouseOver(window)) {
					isPressed = NOTHING;
				}
			}
		}
		// Release player:
		else if (isPressed == PLAYER) {
			isPressed = NOTHING;
		}
		// Release bounds:
		else if (isPressed == RIGHT_BOUND || isPressed == LEFT_BOUND || isPressed == UPPER_BOUND || isPressed == LOWER_BOUND) {
			isPressed = NOTHING;
		}
	}

	// Key events:

	// Move view with arrow keys:
	if (key == "up") {
		viewY--;
	}
	else if (key == "down") {
		viewY++;
	}
	else if (key == "right") {
		viewX++;
	}
	else if (key == "left") {
		viewX--;
	}
}

void CreateLevel::saveAll() {
	// Make sure the player has moved:
	if (playerHasMoved) {
		// Write player location to line 1:
		dataStream << player.getPosition().x << "," << player.getPosition().y << "\n";
	}

	// Write boundary locations to line 2:
	for (int i = 0; i < boundVec.size(); i++) {
		dataStream << boundVec[i]->getPosition().x << "," << boundVec[i]->getPosition().y << ",";
	}
	dataStream << "\n";

	// Write easy enemy locations to line 3:
	for (int i = 0; i < easyEnemyVec.size(); i++) {
		dataStream << easyEnemyVec[i]->getPosition().x << "," << easyEnemyVec[i]->getPosition().y << ",";
	}
	dataStream << "\n";

	// Write level boundary locations to line 4:
	// Order: upper, lower, right, left
	dataStream << upperBound.getPosition().x << "," << upperBound.getPosition().y << ","
		<< lowerBound.getPosition().x << "," << lowerBound.getPosition().y << ","
		<< rightBound.getPosition().x << "," << rightBound.getPosition().y << ","
		<< leftBound.getPosition().x << "," << leftBound.getPosition().y << ",";

	dataStream << "\n";
	data = dataStream.str();

	saveFile.saveFileDialog(data);
}

void CreateLevel::openProject() {
	// Get file:
	openFile.openFileDialog(fileName);
	std::ifstream levelFile(fileName);

	// Load all data from the file:
	boundVec.clear();
	easyEnemyVec.clear();
	playerHasMoved = true;
	loadHandler.loadFile(levelFile, player, boundVec, boundTexture, easyEnemyVec, easyEnemyTexture,
		upper, lower, right, left);

	// Account for the boundaries:
	boundCount = 0;
	for (int i = 0; i < boundVec.size(); i++) {
		boundCount++;
	}
	// Account for the enemies:
	easyEnemyCount = 0;
	for (int i = 0; i < easyEnemyVec.size(); i++) {
		easyEnemyCount++;
	}
}

CreateLevel::~CreateLevel() {

}

bool CreateLevel::isMouseOver(sf::RenderWindow &window, sf::Text &text) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = text.getPosition().x;
	int btnPosY = text.getPosition().y;

	int btnxPosWidth = text.getPosition().x + text.getGlobalBounds().width;
	int btnyPosHeight = text.getPosition().y + text.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 10 && mouseX > btnPosX - 10 && mouseY < btnyPosHeight + 10 && mouseY > btnPosY - 10) {
		return true;
	}
	return false;
}