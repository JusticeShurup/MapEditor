#include "TilesetsMenu.h"
#include <iostream>

#include "TilesetsMenuMainState.h"
#include "TilesetsMenuPaletteState.h"

TilesetsMenu::TilesetsMenu(sf::Vector2f size, sf::Vector2f position, Tileset* current_tileset) :
	current_tileset(current_tileset)
{

	menu_state = new TilesetsMenuMainState(this, current_tileset);

	open_menu_button_texture.loadFromFile("button2.png");
	open_menu_button = sf::RectangleShape(sf::Vector2f(100, 100));
	open_menu_button.setTexture(&open_menu_button_texture);

	background_texture.loadFromFile("main_tilesetmenu.png");
	background = sf::RectangleShape(size);
	background.setPosition(position);
	background.setTexture(&background_texture);

	is_open = false;
}

void TilesetsMenu::setPosition(float x, float y) {
	background.setPosition(sf::Vector2f(x, y));
	open_menu_button.setPosition(x + background.getGlobalBounds().width - 1,
								 y + background.getGlobalBounds().height / 2 - open_menu_button.getGlobalBounds().height);
}

void TilesetsMenu::setPosition(sf::Vector2f position) {
	background.setPosition(position);
	open_menu_button.setPosition(position.x + background.getGlobalBounds().width,
								 position.y + background.getGlobalBounds().height / 2 - open_menu_button.getGlobalBounds().height);
}

sf::FloatRect TilesetsMenu::getGlobalBounds() {
	return background.getGlobalBounds();
}

sf::RectangleShape* TilesetsMenu::getBackground() {
	return &background;
}

sf::Vector2f TilesetsMenu::getPosition() {
	return background.getPosition();
}

void TilesetsMenu::setSize(float width, float height) {
	background.setSize(sf::Vector2f(width, height));
}

void TilesetsMenu::setSize(sf::Vector2f size) {
	background.setSize(size);
}

void TilesetsMenu::setCurrentTileset(Tileset* tileset) {
	menu_state->setCurrentTileset(tileset);
}

bool TilesetsMenu::contains(sf::Vector2f mouse_pos) {
	return background.getGlobalBounds().contains(mouse_pos) || open_menu_button.getGlobalBounds().contains(mouse_pos);
}

sf::Vector2f TilesetsMenu::getSize() {
	return background.getSize();
}

void TilesetsMenu::setTilesetsMenuState(TilesetsMenuState* menu_state) {
	delete this->menu_state;
	this->menu_state = menu_state;
}

bool TilesetsMenu::open() {
	is_open = is_open ? false : true;
	return is_open;
}

void TilesetsMenu::update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) {
	
	if (open_menu_button.getGlobalBounds().contains(mouse_pos) && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		camera.setCanZoom(!open());
	}

	//std::cout << background.getPosition().x << " " << background.getPosition().y << " " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
	setPosition(is_open ? camera.getView().getCenter().x - camera.getView().getSize().x / 2 : camera.getView().getCenter().x - camera.getView().getSize().x /2 - background.getGlobalBounds().width,
				camera.getView().getCenter().y - camera.getView().getSize().y / 2);
	
	if (is_open) {
		menu_state->update(event, camera, mouse_pos);
	}
}

void TilesetsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	if (is_open) {
		target.draw(background);
		menu_state->render(target);
	}
	target.draw(open_menu_button);
}