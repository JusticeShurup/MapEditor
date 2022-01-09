#ifndef _GAME_OBJECTS_MENU_PALETTE_STATE_H_
#define _GAME_OBJECTS_MENU_PALETTE_STATE_H_

#include "GameObjectsMenuState.h"

class GameObjectsMenuPaletteState :
    public GameObjectsMenuState
{
public:
	GameObjectsMenuPaletteState(GameObjectsMenu* gameobjs_menu, std::string category_name, GameObject* current_gameobj);
	~GameObjectsMenuPaletteState();

	void update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) override;
	void render(sf::RenderTarget& target) override;

private:
	std::vector<GameObject*> gameobjs_palette;
	std::vector<GameObject*> gameobjs_native_size;

	sf::Texture* pallete_texture;
	sf::Texture* arrow_texture;
	sf::Texture* main_menu_texture;

	sf::RectangleShape* arrow_left_button;
	sf::RectangleShape* arrow_right_button;
	sf::RectangleShape* main_menu_button;

	sf::Font font;
	sf::Text* category_name;
};
#endif

