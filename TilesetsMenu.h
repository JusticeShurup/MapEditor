#ifndef _TILESETS_MENU_H_
#define _TILESETS_MENU_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Camera.h"

#include "TilesetsMenuState.h"

class TilesetsMenu : public sf::Drawable
{
public:
	TilesetsMenu(sf::Vector2f size, sf::Vector2f position, Tileset* current_tileset);

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	sf::RectangleShape* getBackground();

	void setSize(float widht, float height);
	void setSize(sf::Vector2f size);
	void setCurrentTileset(Tileset* tileset);
	
	bool contains(sf::Vector2f mouse_pos);

	sf::Vector2f getSize();

	void setTilesetsMenuState(TilesetsMenuState* menu_state);

	bool open();

	void update(sf::Event& event, Camera& camera, sf::Vector2f mouse_position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	TilesetsMenuState* menu_state;
	Tileset* current_tileset;

	std::vector<Button*> buttons;

	sf::Texture background_texture;
	sf::RectangleShape background;

	sf::Texture open_menu_button_texture;
	sf::RectangleShape open_menu_button;

	bool is_open;
};
#endif

