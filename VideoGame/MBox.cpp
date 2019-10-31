#include <iostream>
#include <SFML/Graphics.hpp>

#include "Button.h"

#include "MBox.h"

MBox::MBox(sf::Font &font) {
	message.setFont(font);
	message.setCharacterSize(15);
	message.setPosition(10, 10);

	btnFont = &font;
}

void MBox::show(std::string msg, std::string name) {

	// Set message:
	message.setString(msg);
	sizeX = message.getLocalBounds().width + 100;
	sizeY = message.getLocalBounds().height + 100;

	// Create window:
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - sizeX / 2, (sf::VideoMode::getDesktopMode().height / 2 - sizeY));

	window.create(sf::VideoMode(sizeX, sizeY), name, sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	Button btnOk("Close", { 100, 30 }, 15, sf::Color::Red, sf::Color::Black);
	btnOk.setFont(*btnFont);
	btnOk.setPosition({ 10, 70 });

	//Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {
			case sf::Event::MouseButtonPressed:
				if (btnOk.isMouseOver(window)) {}
				else {
					break;
				}
			case sf::Event::Closed:
				window.close();
			}

		}
		window.clear();
		btnOk.drawTo(window);
		window.draw(message);
		window.display();
	}
}