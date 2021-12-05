#ifndef _EDITOR_H_
#define _EDITOR_H_
#include "TileSet.h"
#include "SFML/System.hpp"
#include <vector>
#include "TextureContainer.h"

class Editor
{
public: 
	Editor();
	Editor(sf::RenderWindow* window, sf::Event *event);
	~Editor();

	void initWindow();
	void initMap();
	void initPalette();

	void rotateCurrentTileset(int8_t direction);// 1 - Clockwise, -1 - CounterClockWise

	void update();
	void updateFile();

	void render();

private: 
	sf::RenderWindow *window;
	sf::Event *event;
	TextureContainer* textureContainer;

	std::vector<std::vector<std::string>> map;
	std::vector<std::vector<Tileset>> tilesets;
	std::vector<std::vector<Tileset>> tilesets_palette;

	Tileset* currentTileset;
};
#endif
