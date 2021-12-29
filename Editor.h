#ifndef _EDITOR_H_
#define _EDITOR_H_
#include "TileSet.h"
#include "SFML/System.hpp"
#include <SFML/Window.hpp>
#include <vector>
#include "TextureContainer.h"
#include "TilesetsMenu.h"

class Editor
{
public: 
	Editor();
	Editor(sf::RenderWindow* window, sf::Event *event, Camera* camera, bool* pause);
	~Editor();

	void initWindow();
	void initMap();
	void initPalette();

	void rotateCurrentTileset(int8_t direction);// 1 - Clockwise, -1 - CounterClockWise

	void update(Camera& camera, float delta_time);
	void updateFile();

	void render();

private:

	sf::RenderWindow *window;
	sf::Event *event;
	Camera* camera;

	TextureContainer* textureContainer;

	std::vector<std::vector<std::string>> map;
	std::vector<std::vector<Tileset>> tilesets;

	Tileset* currentTileset;
	bool can_set_tileset;
	bool* pause;
	float time_last_opening; // Time before last opening tilesets menu


	TilesetsMenu tilesets_menu;

};
#endif
