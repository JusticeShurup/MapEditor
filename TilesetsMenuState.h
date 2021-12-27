#ifndef _TILESETS_MENU_STATE_
#define _TILESETS_MENU_STATE_

#include "Button.h"

class TilesetsMenu;

class Camera;
class Tileset;
class TilesetsMenuState

{
protected: 
	TilesetsMenu* tilesets_menu;
	Tileset* current_tileset;

public: 
	TilesetsMenuState(TilesetsMenu* tilesets_menu, Tileset* current_tileset);

	void setTilesetsMenu(TilesetsMenu* tilesets_menu);
	void setCurrentTileset(Tileset* tileset);
	void setNewState(TilesetsMenuState* menu_state);

	virtual void update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) = 0;
	virtual void render(sf::RenderTarget& window) = 0;
};
#endif
