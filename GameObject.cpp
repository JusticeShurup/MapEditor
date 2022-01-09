#include "GameObject.h"

GameObject::GameObject(sf::Vector2f obj_size, sf::Vector2f hitbox_size) {
	object = new sf::RectangleShape(obj_size);
	hitbox = sf::RectangleShape(hitbox_size);
	is_load_from_file = false;
}

GameObject::GameObject(std::string filename, sf::Vector2f obj_size, sf::Vector2f obj_pos, sf::Vector2f hitbox_size, sf::Vector2f hitbox_pos, std::string name) {
	this->name = name;

	is_load_from_file = true;
	texture = new sf::Texture;
	texture->loadFromFile(filename);

	object = new sf::RectangleShape(obj_size);
	object->setOutlineColor(sf::Color::Green);
	
	hitbox = sf::RectangleShape(hitbox_size);
	hitbox.setFillColor(sf::Color(255, 255, 255, 128));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox_delta_position = hitbox_pos;

	object->setTexture(texture);
	setPosition(obj_pos);
}

GameObject::GameObject(sf::Texture* texture, sf::Vector2f obj_size, sf::Vector2f obj_pos, sf::Vector2f hitbox_size, sf::Vector2f hitbox_pos, std::string name) {
	this->name = name;
	is_load_from_file = false;

	object = new sf::RectangleShape(obj_size);
	object->setOutlineColor(sf::Color::Green);

	hitbox = sf::RectangleShape(hitbox_size);
	hitbox.setFillColor(sf::Color(255, 255, 255, 128));
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox_delta_position = hitbox_pos;

	this->texture = texture;
	object->setTexture(texture);
	setPosition(obj_pos);
}

GameObject::~GameObject() {
	if (is_load_from_file) delete texture;
}

sf::RectangleShape* GameObject::getObjectShape() {
	return object;
}

sf::RectangleShape* GameObject::getHitboxShape() {
	return &hitbox;
}

void GameObject::setPosition(sf::Vector2f obj_pos) {
	object->setPosition(obj_pos);
	hitbox.setPosition(obj_pos.x + hitbox_delta_position.x, obj_pos.y + hitbox_delta_position.y);
}

void GameObject::setPosition(float x, float y) {
	object->setPosition(x, y);
	hitbox.setPosition(x + hitbox_delta_position.x, y + hitbox_delta_position.y);
}

void GameObject::setNewHitboxPosition(sf::Vector2f hitbox_pos) {
	hitbox_delta_position = hitbox_pos;
}

sf::Vector2f GameObject::getObjectPosition() {
	return object->getPosition();
}

sf::Vector2f GameObject::getHitboxPosition(){
	return hitbox_delta_position;
}

void GameObject::showObjectOutlines() {
	if (round(object->getOutlineThickness()) == 0)
		object->setOutlineThickness(3);
	else 
		object->setOutlineThickness(0);
}

void GameObject::showHitboxOutlines() {
	is_hitbox_hidden = !is_hitbox_hidden;
	if (round(hitbox.getOutlineThickness()) == 0)
		hitbox.setOutlineThickness(1);
	else
		hitbox.setOutlineThickness(0);
}

void GameObject::setTexture(std::string filename) {
	this->texture->loadFromFile(filename);
	object->setTexture(texture, 1);
}

void GameObject::setTexture(sf::Texture* texture) {
	if (is_load_from_file) delete this->texture;
	this->texture = texture;
	object->setTexture(this->texture, 1);
}

sf::Texture* GameObject::getTexture() {
	return texture;
}

void GameObject::setName(std::string name) {
	this->name = name;
}

std::string GameObject::getName() {
	return name;
}

void GameObject::hideHitbox(bool flag) {
	is_hitbox_hidden = flag;
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*object);
	if (!is_hitbox_hidden) target.draw(hitbox);
}