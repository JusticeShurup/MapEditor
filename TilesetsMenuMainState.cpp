#include "TilesetsMenuMainState.h"

#include "TilesetsMenu.h"
#include "TilesetsMenuPaletteState.h"
#include "Button.h"

TilesetsMenuMainState::TilesetsMenuMainState(TilesetsMenu* tilesets_menu, Tileset* current_tileset) : TilesetsMenuState(tilesets_menu, current_tileset) {
	buttons = std::vector<Button*>({});
	buttons.push_back(new Button(550, 75, -100000, -100000, "Roads", false));
	buttons[0]->setShapeColor("idle", sf::Color(145, 94, 96));
	buttons[0]->setShapeColor("hover", sf::Color::Red);
	buttons[0]->setTextColor("hover", sf::Color::White);
	buttons.push_back(new Button(550, 75, -10000, -10000, "Land", false));
	buttons[1]->setShapeColor("idle", sf::Color(145, 94, 96));
	buttons[1]->setShapeColor("hover", sf::Color::Red);
	buttons[1]->setTextColor("hover", sf::Color::White);

	main_texture = new sf::Texture;
	main_texture->loadFromFile("main_tilesetmenu.png");

	tilesets_menu->getBackground()->setTexture(main_texture);
}

TilesetsMenuMainState::~TilesetsMenuMainState() {
	delete main_texture;
	for (auto button : buttons) {
		delete button;
	}
}


void TilesetsMenuMainState::update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) {
	sf::Vector2f position(camera.getView().getCenter().x - camera.getView().getSize().x / 2,
						  camera.getView().getCenter().y - camera.getView().getSize().y / 2);
	
	current_tileset->setPosition(position.x + tilesets_menu->getGlobalBounds().width - current_tileset->getShape()->getGlobalBounds().width - 32,
								 position.y + current_tileset->getShape()->getGlobalBounds().height - 32);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->setPosition(position.x + tilesets_menu->getGlobalBounds().width / 2 - buttons[i]->getShape()->getGlobalBounds().width / 2 + 5,
								position.y + buttons[i]->getText()->getGlobalBounds().height + 100 * (i+1));
		buttons[i]->update(mouse_pos, event);
		if (buttons[i]->isClicked()) {
			tilesets_menu->setTilesetsMenuState(new TilesetsMenuPaletteState(tilesets_menu, buttons[i]->getText()->getString(), current_tileset));
			break;
		}
	}
}

void TilesetsMenuMainState::render(sf::RenderTarget& target) {
	for (auto button : buttons) {
		target.draw(*button);
	}
	target.draw(*current_tileset);
}