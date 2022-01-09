#ifndef _GAME_OBJECTS_MENU_STATE_H_
#define _GAME_OBJECTS_MENU_STATE_H_
#include "Button.h"

class GameObjectsMenu;
class GameObject;
class Camera;

class GameObjectsMenuState
{
protected:
	GameObjectsMenu* gameobjs_menu;
	GameObject* current_gameobj;

public:
	GameObjectsMenuState(GameObjectsMenu* gameobjs_menu, GameObject* current_gameobject);

	void setTilesetsMenu(GameObjectsMenu* gameobjects_menu);
	void setCurrentGameObject(GameObject* gameobject);
	void setNewState(GameObjectsMenuState* menu_state);

	virtual void update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) = 0;
	virtual void render(sf::RenderTarget& window) = 0;
};
#endif