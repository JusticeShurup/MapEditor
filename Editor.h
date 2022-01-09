#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "Tileset.h"
#include "SFML/System.hpp"
#include <SFML/Window.hpp>
#include <vector>
#include "TextureContainer.h"
#include "TilesetsMenu.h"
#include "GameObjectsMenu.h"
#include "MapEditorState.h"

class Editor
{
public: 
	Editor();
	Editor(sf::RenderWindow* window, sf::Event *event, Camera* camera, bool* pause);
	~Editor();

	void initMap();

	void rotateCurrentTileset(int8_t direction);// 1 - Clockwise, -1 - CounterClockWise

	void update(Camera& camera, float delta_time);

	void render();

	void setNewState(MapEditorState* state);
	friend class FirstLevelEditorState;
	friend class SecondLevelEditorState;
private:
	sf::Texture* house_texture;
	GameObject* house;

	MapEditorState* state;

	sf::RenderWindow *window;
	sf::Event *event;
	Camera* camera;

	TextureContainer* textureContainer;

	std::vector<std::vector<std::string>> map;

	std::vector<std::vector<Tileset>> tilesets;
	std::vector<GameObject> gameobjects;

	Tileset* current_tileset;
	TilesetsMenu tilesets_menu;

	GameObject* current_gameobj;
	GameObjectsMenu gameobjs_menu;

	bool can_set_tileset;
	bool* pause;
	float time_last_opening; // Time before last opening tilesets menu

	
};
#endif
