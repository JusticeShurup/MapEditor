#ifndef _GAME_OBJECTS_MENU_MAIN_STATE_H_
#define _GAME_OBJECTS_MENU_MAIN_STATE_H_
#include "GameObjectsMenuState.h"
class GameObjectsMenuMainState :
    public GameObjectsMenuState
{
public: 
	GameObjectsMenuMainState(GameObjectsMenu* tilesets_menu, GameObject* current_tileset);
	~GameObjectsMenuMainState();

	void update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) override;
	void render(sf::RenderTarget& window);
private: 
	std::vector<Button*> buttons;
	sf::Texture* main_texture;
};
#endif