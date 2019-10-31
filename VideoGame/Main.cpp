#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "LoadLevel.h"
#include "CreateLevel.h"

#include "Textbox.h"
#include "Button.h"
#include "MBox.h";

#include "Inventory.h"
#include "Sword.h"

#include "Level1.h"
#include "Level2.h"

const int SCR_WIDTH = 900;
const int SCR_HEIGHT = 900;

int main() {
	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Ben's C++/SFML Game", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	// Setup view:
	sf::View mainView;
	mainView.reset(sf::FloatRect(0, 0, SCR_WIDTH, SCR_HEIGHT));

	// Player movements:
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;

	float moveSpeed = 0.7;

	// Inventory:
	Inventory inv;

	// Player:
	Player player;
	player.setSprite("resources/Player.png");
	player.setPosition({ 10, 10 });
	player.drawTo(window);


	// Create font:
	sf::Font font;
	if (!font.loadFromFile("resources/terminal.otf"))
		std::cerr << "Error\n";

	// Levels:
	int levelState = 0;
	Level1 lvl1;
	Level2 lvl2;

	LoadLevel loadLevel;
	CreateLevel createLevel(font);

	std::string strEvent = "";
	std::string keyEvent = "";

	// Label title:
	sf::Text lblTitle;
	lblTitle.setFont(font);
	lblTitle.setString("Ben's C++/SFML\n            Game");
	lblTitle.setCharacterSize(100);
	lblTitle.setColor(sf::Color(51, 153, 255));

	// Center title:
	lblTitle.setPosition(sf::Vector2f(900 / 2.0f - 395, 900 / 2.0f - 420));

	// Label name:
	sf::Text lblName;
	lblName.setFont(font);
	lblName.setString("Enter your name: ");
	lblName.setCharacterSize(40);
	lblName.setColor(sf::Color::White);

	// Center label:
	lblName.setPosition(sf::Vector2f(900 / 2.0f - 170, 900 / 2.0f - 130));

	// Name Textbox:
	Textbox text1(20, sf::Color::White, true);
	text1.setPosition({ 100, 50 });
	text1.setLimit(true, 30);
	text1.setFont(font);

	//Center textbox:
	text1.setPosition(sf::Vector2f(900 / 2.0f - 170, 900 / 2.0f - 50));

	// Play button:
	Button btn1("Play Game", { 170, 50 }, 17, sf::Color::Green, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition(sf::Vector2f(900 / 2.0f - 170, 900 / 2.0f));

	// Create level button:
	Button btnCreate("Create Level", { 170, 50 }, 17, sf::Color(244, 197, 66), sf::Color::Black);
	btnCreate.setFont(font);
	btnCreate.setPosition(sf::Vector2f(900 / 2.0f - 170, 900 / 2.0f + 70));

	// Load level button:
	Button btnLoad("Load Level", { 170, 50 }, 17, sf::Color::Magenta, sf::Color::Black);
	btnLoad.setFont(font);
	btnLoad.setPosition(sf::Vector2f(900 / 2.0f - 170, 900 / 2.0f + 140));

	// Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			text1.setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			text1.setSelected(false);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			
		}

		// Player movement and camera movement:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			up = true;
			keyEvent = "up";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			down = true;
			keyEvent = "down";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			right = true;
			keyEvent = "right";
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			left = true;
			keyEvent = "left";
		}

		// Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				text1.typedOn(Event);
			case sf::Event::MouseMoved:
				// Create level stuff:
				if (levelState == -1) {
					createLevel.inputEvents(strEvent, keyEvent, window);
				}

				// Main menu:
				if (btn1.isMouseOver(window)) {
					// Highlight buttons when mouse is over them:
					btn1.setBackColor(sf::Color(153, 204, 0));
				}
				else {
					btn1.setBackColor(sf::Color(102, 102, 51));
				}

				if (btnLoad.isMouseOver(window)) {
					btnLoad.setBackColor(sf::Color(204, 153, 255));
				}
				else {
					btnLoad.setBackColor(sf::Color::Magenta);
				}

				if (btnCreate.isMouseOver(window)) {
					btnCreate.setBackColor(sf::Color::Yellow);
				}
				else {
					
					btnCreate.setBackColor(sf::Color(244, 197, 66));
				}
				break;

			case sf::Event::MouseButtonPressed:
				// Main menu:

				// Start game:
				if (btn1.isMouseOver(window)) {
					player.setName(text1.getText(), font);
					levelState = 1;
				}
				// Create level:
				else if (btnCreate.isMouseOver(window)) {
					levelState = -1;
				}
				// Load level:
				else if (btnLoad.isMouseOver(window)) {
					loadLevel.loadLevel(player);
					levelState = -2;
				}

				// Create level stuff:
				strEvent = "pressed";

				// In-game mouse stuff:
				if (levelState > 0) {
					// Have player attack:
					player.setAttacking(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				// Create level stuff:
				strEvent = "released";

				// In-game:
				if (levelState > 0) {
					// Stop attacking:
					player.setAttacking(false);
				}
			// Keys released:
			case sf::Event::KeyReleased:
				// Movement:
				if (Event.key.code == sf::Keyboard::Key::W) {
					up = false;
					keyEvent = "";
				}
				else if (Event.key.code == sf::Keyboard::Key::S) {
					down = false;
					keyEvent = "";
				}
				else if (Event.key.code == sf::Keyboard::Key::D) {
					right = false;
					keyEvent = "";
				}
				else if (Event.key.code == sf::Keyboard::Key::A) {
					left = false;
					keyEvent = "";
				}

			// Search inventory:
			case sf::Event::KeyPressed:
				// If key is a number 1-9
				if (Event.key.code >= 27 && Event.key.code <= 35) {
					// Set index to the corresponding number - 1:
					int index = Event.key.code - 27;
					// Make sure the index position exists:
					if (inv.getInventory().size() >= index + 1) {
						inv.setSelected(inv.getInventory()[index]);
					}
				}
			}

		}
		window.clear();

		// Set view
		window.setView(mainView);

		// Main menu handler:
		if (levelState == 0) {
			text1.drawTo(window);
			btn1.drawTo(window);
			btnLoad.drawTo(window);
			btnCreate.drawTo(window);
			window.draw(lblName);
			window.draw(lblTitle);
		}
		if (levelState != 0) {
			text1.setPosition({ 10432423, 423432 });
			btn1.setPosition({ 10432423, 423432 });
			btnLoad.setPosition({ 10432423, 423432 });
			btnCreate.setPosition({ 10432423, 423432 });
			lblName.setPosition({ 10432423, 423432 });
			lblTitle.setPosition({ 10432423, 423432 });
		}

		// Create levels:
		if (levelState == -1) {
			createLevel.createLevel(window, mainView);
			createLevel.inputEvents(strEvent, keyEvent, window);
		}

		// Loaded levels:
		if (levelState == -2) {
			loadLevel.runLevel(window, player);
		}

		// For all levels:
		if (levelState > 0 || levelState == -2) {
			// Have inventory follow view:
			inv.setPosition({ mainView.getCenter().x - SCR_WIDTH / 2, mainView.getCenter().y + SCR_HEIGHT / 4 + 145});
			// Move player:
			if (up) {
				player.move({ 0, -moveSpeed });
			}
			else if (down) {
				player.move({ 0, moveSpeed });
			}
			else if (right) {
				player.move({ moveSpeed, 0 });
			}
			else if (left) {
				player.move({ -moveSpeed, 0 });
			}
			
			// Load and run level 1:
			if (levelState == 1 && !lvl1.isLoaded()) {
				lvl1.loadLevel();
				lvl1.setLoaded(true);
			}
			else if (levelState == 1 && lvl1.isLoaded()) {
				lvl1.runLevel(window, player, inv, mainView, SCR_WIDTH, SCR_HEIGHT, levelState);
			}
			// Load and run level 2:
			if (levelState == 2 && !lvl2.isLoaded()) {
				lvl2.loadLevel();
				lvl2.setLoaded(true);
			}
			else if (levelState == 2 && lvl2.isLoaded()) {
				lvl2.runLevel(window, player, inv, mainView, SCR_WIDTH, SCR_HEIGHT, levelState);
			}

			// Draw Player:
			player.drawTo(window);

			// Draw inventory:
			inv.drawTo(window);
		}
		window.display();
	}
}