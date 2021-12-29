#ifndef _TILESETS_MENU_MAIN_STATE_H_
#define _TILESETS_MENU_MAIN_STATE_H_

#include "TilesetsMenuState.h"

class TilesetsMenuMainState : 
	public TilesetsMenuState
{
public: 
	TilesetsMenuMainState(TilesetsMenu* tilesets_menu, Tileset* current_tileset);
	~TilesetsMenuMainState();

	void update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) override;
	void render(sf::RenderTarget& window);

private: 
	std::vector<Button*> buttons;

	sf::Texture* main_texture;
};
#endif
