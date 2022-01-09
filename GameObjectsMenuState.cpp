#include "GameObjectsMenuState.h"
#include "GameObjectsMenu.h"

GameObjectsMenuState::GameObjectsMenuState(GameObjectsMenu* gameobjs_menu, GameObject* current_gameobj) : gameobjs_menu(gameobjs_menu), current_gameobj(current_gameobj) {}

void GameObjectsMenuState::setTilesetsMenu(GameObjectsMenu* gameobjs_menu) {
	this->gameobjs_menu = gameobjs_menu;
}

void GameObjectsMenuState::setCurrentGameObject(GameObject* gameobj) {
	current_gameobj = gameobj;
}

void GameObjectsMenuState::setNewState(GameObjectsMenuState* menu_state) {
	gameobjs_menu->setGameObjectsMenuState(menu_state);
}