#ifndef _TILESETS_MENU_PALETTE_STATE_H_
#define _TILESETS_MENU_PALETTE_STATE_H_

#include "TilesetsMenuState.h"
#include "Tileset.h"
#include <vector>
class TilesetsMenuPaletteState 
	: public TilesetsMenuState
{
public: 
	TilesetsMenuPaletteState(TilesetsMenu* tilesets_menu, std::string category_name, Tileset* current_tileset);
	~TilesetsMenuPaletteState();

	void update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) override;
	void render(sf::RenderTarget& target) override;

private: 
	std::vector<Tileset*> tilesets_palette;

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