#include "Tileset.h"
#include <iostream>

Tileset::Tileset() {
	shape = new sf::RectangleShape(sf::Vector2f(32, 32));
	shape->setOutlineColor(sf::Color::Green);
	texture = nullptr;
}

Tileset::Tileset(sf::Vector2f position) {
	shape = new sf::RectangleShape(sf::Vector2f(32, 32));
	shape->setOutlineColor(sf::Color::Green);
	shape->setPosition(position);
	texture = nullptr;
}

Tileset::Tileset(std::string filename, std::string sign, sf::Vector2f position) {
	shape = new sf::RectangleShape(sf::Vector2f(32, 32));
	shape->setOutlineColor(sf::Color::Green);
	this->sign = sign;
	setTexture(filename);
	setPosition(position);
}

Tileset::Tileset(sf::Texture* texture, std::string sign, sf::Vector2f position) {
	shape = new sf::RectangleShape(sf::Vector2f(32, 32));
	shape->setOutlineColor(sf::Color::Green);
	this->sign = sign;
	setPosition(position);
	setTexture(texture);
}

void Tileset::setSign(std::string sign) {
	this->sign = sign;
}

std::string Tileset::getSign() {
	return sign;
}

void Tileset::setTexture(std::string filename) {
	if (filename != "null") {
		texture->loadFromFile(filename);
		shape->setTexture(texture);
	}
	else {
		shape->setTexture(nullptr);
	}
}

void Tileset::setTexture(sf::Texture* texture) {
	this->texture = texture;
 	shape->setTexture(this->texture);
}

sf::Texture* Tileset::getTexture() {
	return texture;
}

void Tileset::setPosition(float x, float y) {
	shape->setPosition(sf::Vector2f(x, y));
}

void Tileset::setPosition(sf::Vector2f pos) {
	shape->setPosition(pos);
}

sf::Vector2f Tileset::getPosition() {
	return shape->getPosition();
}

sf::RectangleShape* Tileset::getShape() {
	return shape;
}

void Tileset::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*shape);
}