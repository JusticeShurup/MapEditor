#include "GameObjectsMenuPaletteState.h"
#include "GameObjectsMenuMainState.h"
#include "GameObjectsMenu.h"
#include "GameObject.h"

#include "TextureContainer.h"
#include <fstream>
#include <iostream>
#include "Camera.h"

GameObjectsMenuPaletteState::GameObjectsMenuPaletteState(GameObjectsMenu* gameobjs_menu, std::string name, GameObject* current_gameobj) : GameObjectsMenuState(gameobjs_menu, current_gameobj) {

	font.loadFromFile("Inconsolata_Condensed-Bold.ttf");
	category_name = new sf::Text(name, font, 50);
	category_name->setFillColor(sf::Color::Red);

	pallete_texture = new sf::Texture;
	pallete_texture->loadFromFile("palette_tilesetmenu.png");
	arrow_texture = new sf::Texture;
	main_menu_texture = new sf::Texture;

	arrow_left_button = new sf::RectangleShape(sf::Vector2f(64, 64));
	arrow_right_button = new sf::RectangleShape(sf::Vector2f(64, 64));
	main_menu_button = new sf::RectangleShape(sf::Vector2f(64, 64));

	gameobjs_menu->getBackground()->setTexture(pallete_texture);
	arrow_texture->loadFromFile("button2.png");
	main_menu_texture->loadFromFile("menu.png");

	arrow_left_button->setTexture(arrow_texture);
	arrow_left_button->setScale(-1.f, 1.f);
	arrow_right_button->setTexture(arrow_texture);
	main_menu_button->setTexture(main_menu_texture);

	/*
		std::map<std::string, std::map<uint8_t, sf::Texture*>> textures = TextureContainer::getInstance()->getTexturesByCathegory(category_name->getString());
		int count = 0;
		for (auto it = textures.begin(); it != textures.end(); it++) {
			gameobjs_palette.emplace_back(new GameObject(it->second[1], it->first, sf::Vector2f(64, 64), sf::Vector2f(-10000, -10000)));
		}
	*/
	auto container = TextureContainer::getInstance();
	std::map<std::string, sf::Texture*> textures = TextureContainer::getInstance()->getGameObjectsTexturesByCathegory(name);
	for (auto it = textures.begin(); it != textures.end(); it++) {
		gameobjs_palette.push_back(new GameObject(it->second, sf::Vector2f(64, 64), sf::Vector2f(-1000, -1000), sf::Vector2f(0, 0), sf::Vector2f(0, 0), it->first));
		gameobjs_native_size.push_back(new GameObject(it->second, container->getGameObjectNativeSize(it->first), sf::Vector2f(-1000, -1000), container->getGameObjectHitboxSize(it->first), container->getGameObjectHitboxPosition(it->first), it->first));
	}
}

GameObjectsMenuPaletteState::~GameObjectsMenuPaletteState() {
	delete arrow_texture;
	delete main_menu_texture;

	delete pallete_texture;
	delete arrow_left_button;
	delete arrow_right_button;
	delete main_menu_button;

	for (auto& gameobj : gameobjs_palette) delete gameobj;
	for (auto& gameobj : gameobjs_native_size) delete gameobj;

	delete category_name;
}

void GameObjectsMenuPaletteState::update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) {

	float x0 = camera.getView().getCenter().x - camera.getView().getSize().x / 2;
	float y0 = camera.getView().getCenter().y - camera.getView().getSize().y / 2;


	category_name->setPosition(x0 + gameobjs_menu->getGlobalBounds().width / 2 - category_name->getGlobalBounds().width / 2,
							   y0 + category_name->getGlobalBounds().height / 2 + 6);

	arrow_left_button->setPosition(x0 + arrow_left_button->getGlobalBounds().width + 30,
								   y0 + gameobjs_menu->getSize().y - arrow_left_button->getGlobalBounds().height - 25);

	arrow_right_button->setPosition(x0 + gameobjs_menu->getSize().x - arrow_right_button->getGlobalBounds().width - 30,
									y0 + gameobjs_menu->getSize().y - arrow_left_button->getGlobalBounds().height - 25);

	main_menu_button->setPosition(x0 + gameobjs_menu->getSize().x / 2 - main_menu_button->getGlobalBounds().width / 2,
								  y0 + gameobjs_menu->getSize().y - arrow_left_button->getGlobalBounds().height - 25);

	int current_gameobj = 0;
	int count_gameobjs = gameobjs_palette.size();
	for (int i = 0; i <= gameobjs_palette.size() / 5; i++) {
		for (int j = 0; j < (count_gameobjs >= 5 ? 5 : count_gameobjs); j++) {
			gameobjs_palette[current_gameobj]->setPosition(x0 + (j + 1) * 76 + j * 20 + 20,
														   y0 + (i + 1) * 126 - 1 - i * 30 + category_name->getGlobalBounds().height);

			if (gameobjs_palette[current_gameobj]->getObjectShape()->getGlobalBounds().contains(mouse_pos)) {
				gameobjs_palette[current_gameobj]->getObjectShape()->setOutlineThickness(6);
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
					std::string name = gameobjs_palette[current_gameobj]->getName();
					this->current_gameobj->setName(name);
					this->current_gameobj->getObjectShape()->setSize(TextureContainer::getInstance()->getGameObjectNativeSize(name));
					this->current_gameobj->getHitboxShape()->setSize(TextureContainer::getInstance()->getGameObjectHitboxSize(name));
					this->current_gameobj->setNewHitboxPosition(TextureContainer::getInstance()->getGameObjectHitboxPosition(name));
					this->current_gameobj->setTexture(TextureContainer::getInstance()->getGameObjectTexture(name));
				}
			}
			else {
				gameobjs_palette[current_gameobj]->getObjectShape()->setOutlineThickness(0);
			}
			current_gameobj++;
		}
		count_gameobjs -= 5;

	}

	if (main_menu_button->getGlobalBounds().contains(mouse_pos) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		gameobjs_menu->setGameObjectsMenuState(new GameObjectsMenuMainState(gameobjs_menu, this->current_gameobj));
	}
}

void GameObjectsMenuPaletteState::render(sf::RenderTarget& target) {
	target.draw(*category_name);
	for (auto gameobj : gameobjs_palette) {
		target.draw(*gameobj);
	}
	target.draw(*arrow_left_button);
	target.draw(*arrow_right_button);
	target.draw(*main_menu_button);
}