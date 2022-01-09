#include "TilesetsMenuPaletteState.h"
#include "TilesetsMenu.h"
#include "TilesetsMenuMainState.h"
#include "TextureContainer.h"
#include <fstream>
#include <iostream>
#include "Camera.h"

TilesetsMenuPaletteState::TilesetsMenuPaletteState(TilesetsMenu* tilesets_menu, std::string name, Tileset* current_tileset) : TilesetsMenuState(tilesets_menu, current_tileset) {

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

	tilesets_menu->getBackground()->setTexture(pallete_texture);
	arrow_texture->loadFromFile("button2.png");
	main_menu_texture->loadFromFile("menu.png");
	
	arrow_left_button->setTexture(arrow_texture);
	arrow_left_button->setScale(-1.f, 1.f);
	arrow_right_button->setTexture(arrow_texture);
	main_menu_button->setTexture(main_menu_texture);

	std::map<std::string, std::map<uint8_t, sf::Texture*>> textures = TextureContainer::getInstance()->getTilesetsTexturesByCathegory(category_name->getString());
	int count = 0;
	for (auto it = textures.begin(); it != textures.end(); it++) {
		tilesets_palette.emplace_back(new Tileset(it->second[1], it->first, sf::Vector2f(64, 64), sf::Vector2f(-10000, -10000), 1));
	}
}

TilesetsMenuPaletteState::~TilesetsMenuPaletteState() {
	delete arrow_texture;
	delete main_menu_texture;

	delete pallete_texture;
	delete arrow_left_button;
	delete arrow_right_button;
	delete main_menu_button;

	for (auto& tileset : tilesets_palette) delete tileset;

	delete category_name;
}

void TilesetsMenuPaletteState::update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) {

	float x0 = camera.getView().getCenter().x - camera.getView().getSize().x / 2;
	float y0 = camera.getView().getCenter().y - camera.getView().getSize().y / 2;


	category_name->setPosition(x0 + tilesets_menu->getGlobalBounds().width / 2 - category_name->getGlobalBounds().width / 2,
							   y0 + category_name->getGlobalBounds().height / 2 + 6);

	arrow_left_button->setPosition(x0 + arrow_left_button->getGlobalBounds().width + 30,
								   y0 + tilesets_menu->getSize().y - arrow_left_button->getGlobalBounds().height - 25);
	
	arrow_right_button->setPosition(x0 + tilesets_menu->getSize().x - arrow_right_button->getGlobalBounds().width -30, 
									y0 + tilesets_menu->getSize().y - arrow_left_button->getGlobalBounds().height - 25);

	main_menu_button->setPosition(x0 + tilesets_menu->getSize().x / 2 - main_menu_button->getGlobalBounds().width/2, 
								  y0 + tilesets_menu->getSize().y - arrow_left_button->getGlobalBounds().height - 25);

	int current_tileset = 0;
	int count_tilesets = tilesets_palette.size();
	for (int i = 0; i <= tilesets_palette.size()/5; i++) {
		for (int j = 0; j < (count_tilesets >= 5 ? 5 : count_tilesets); j++) {
			tilesets_palette[current_tileset]->setPosition(x0 + (j + 1) * 76 + j * 20 + 20,
														   y0 + (i + 1) * 126 - 1 - i * 30 + category_name->getGlobalBounds().height);

			if (tilesets_palette[current_tileset]->getShape()->getGlobalBounds().contains(mouse_pos)) {
				tilesets_palette[current_tileset]->getShape()->setOutlineThickness(6);
				if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
					this->current_tileset->setSost(1);
					this->current_tileset->setImage(TextureContainer::getInstance()->getTilesetTexture(tilesets_palette[current_tileset]->getSign(), 1));
					this->current_tileset->setTexture(TextureContainer::getInstance()->getTilesetLink(tilesets_palette[current_tileset]->getSign()));
					this->current_tileset->setSign(tilesets_palette[current_tileset]->getSign());
				}
			}
			else {
				tilesets_palette[current_tileset]->getShape()->setOutlineThickness(0);
			}
			current_tileset++;
		}
		count_tilesets-=5;

	}

	if (main_menu_button->getGlobalBounds().contains(mouse_pos) && event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		tilesets_menu->setTilesetsMenuState(new TilesetsMenuMainState(tilesets_menu, this->current_tileset));
	}
}

void TilesetsMenuPaletteState::render(sf::RenderTarget& target) {
	target.draw(*category_name);
	for (auto tileset : tilesets_palette) {
		target.draw(*tileset);
	}
	target.draw(*arrow_left_button);
	target.draw(*arrow_right_button);
	target.draw(*main_menu_button);
}