#include "TilesetsMenuState.h"
#include "TilesetsMenu.h"
#include "Tileset.h"
#include <iostream>

TilesetsMenuState::TilesetsMenuState(TilesetsMenu* tilesets_menu, Tileset* current_tileset) : tilesets_menu(tilesets_menu), current_tileset(current_tileset) {}

void TilesetsMenuState::setTilesetsMenu(TilesetsMenu* tilesets_menu) {
	this->tilesets_menu = tilesets_menu;
}

void TilesetsMenuState::setCurrentTileset(Tileset* tileset) {
	current_tileset = tileset;
}

void TilesetsMenuState::setNewState(TilesetsMenuState* menu_state) {
	tilesets_menu->setTilesetsMenuState(menu_state);
}
