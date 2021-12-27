#include "TilesetsMenuMainState.h"

#include "TilesetsMenu.h"
#include "TilesetsMenuPaletteState.h"

TilesetsMenuMainState::TilesetsMenuMainState(TilesetsMenu* tilesets_menu, Tileset* current_tileset) : TilesetsMenuState(tilesets_menu, current_tileset) {
	buttons =  std::vector<Button*>({});
	buttons.push_back(new Button(0, 0, 0, 0, "Roads", 50));
	buttons.push_back(new Button(0, 0, 0, 0, "Land", 50));
}

TilesetsMenuMainState::~TilesetsMenuMainState() {
	for (auto button : buttons) {
		delete button;
	}
}


void TilesetsMenuMainState::update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) {
	sf::Vector2f position(camera.getView().getCenter().x - camera.getView().getSize().x / 2,
						  camera.getView().getCenter().y - camera.getView().getSize().y / 2);
	
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->setPosition(position.x + tilesets_menu->getGlobalBounds().width / 2 - buttons[i]->getText().getGlobalBounds().width / 2, position.y + buttons[i]->getText().getGlobalBounds().height + 100 * (i+1));
		buttons[i]->update(mouse_pos, event);
		if (buttons[i]->isClicked()) {
			tilesets_menu->setTilesetsMenuState(new TilesetsMenuPaletteState(tilesets_menu, buttons[i]->getText().getString(), current_tileset));
			break;
		}
	}
}

void TilesetsMenuMainState::render(sf::RenderTarget& target) {
	for (auto button : buttons) {
		target.draw(*button);
	}
}