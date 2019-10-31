#include "Transitions.h"

Transitions::Transitions() {
	effect.setSize({ 4000, 4000 });
	effect.setFillColor(sf::Color::Black);
	effect.setPosition({ 500,500 });
}

void Transitions::fadeEffect(sf::RenderWindow &window) {
	window.draw(effect);
}


Transitions::~Transitions() {
}
