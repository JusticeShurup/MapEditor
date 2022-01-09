#include "Editor.h"
#include <fstream>
#include <iostream>
#include <string>
#include "FirstLevelEditorState.h"
#include "SecondLevelEditorState.h"

Editor::Editor()
	: tilesets_menu(TilesetsMenu(sf::Vector2f(1920/3, 1080), sf::Vector2f(0, 0), current_tileset)), 
	  gameobjs_menu(GameObjectsMenu(sf::Vector2f(1920/3, 1080), sf::Vector2f(0, 0), current_gameobj)),
	  camera(new Camera(1920/2, 1920/2, 1000, 1000))
{}

Editor::Editor(sf::RenderWindow* window, sf::Event *event, Camera* camera, bool* pause) :
	house_texture(new sf::Texture),
	current_gameobj(new GameObject(house_texture, sf::Vector2f(500, 500), sf::Vector2f(446, -50), sf::Vector2f(300, 0), sf::Vector2f(8, 104), "house")),
	tilesets_menu(TilesetsMenu(sf::Vector2f(1920/3, 1080), sf::Vector2f(0, 0), current_tileset)),
	gameobjs_menu(GameObjectsMenu(sf::Vector2f(1920/3, 1080), sf::Vector2f(0, 0), current_gameobj)),
	camera(camera), 
	pause(pause)
{
	house_texture->loadFromFile("GameObjects/nabrosokjirnogochlena.png");
	textureContainer = TextureContainer::getInstance();
	initMap();
	time_last_opening = 0;
	can_set_tileset = true;
	current_tileset = new Tileset();
	//current_gameobj = new GameObject("GameObjects/Stolb.png", sf::Vector2f(32, 128), sf::Vector2f(446, -50), sf::Vector2f(10, 12), sf::Vector2f(11, 108), "stolb");

	this->window = window;
	this->event = event;

	current_tileset->setImage(TextureContainer::getInstance()->getTilesetTexture("a", 1));
	current_tileset->setTexture(TextureContainer::getInstance()->getTilesetLink("a"));
	current_tileset->setSign(TextureContainer::getInstance()->getTilesetsSigns()[1]);
	current_tileset->getShape()->setSize(sf::Vector2f(64, 64));

	tilesets_menu.setCurrentTileset(current_tileset);
}

Editor::~Editor(){}

void Editor::initMap() {
	std::ifstream f("Map.txt");
	for (int i = 0; i < 40; i++) {
		std::vector<std::string> string;
		for (int j = 0; j < 50; j++) {
			std::string str("");
			f >> str;
			string.push_back(str);
		}
		map.push_back(string);
	}
	f.close();
}

void Editor::rotateCurrentTileset(int8_t direction) {
	if (direction > 0) {
		current_tileset->setSost(current_tileset->getSost() + 1);
		current_tileset->setTexture(TextureContainer::getInstance()->getTilesetTexture(current_tileset->getSign(),
									current_tileset->getSost()));
	}
	else {
		current_tileset->setSost(current_tileset->getSost() - 1);
		current_tileset->setTexture(TextureContainer::getInstance()->getTilesetTexture(current_tileset->getSign(),
									current_tileset->getSost()));
	}

}

void Editor::update(Camera& camera, float delta_time){
	state->update(camera, delta_time);
}

void Editor::render() {
	state->render();
}

void Editor::setNewState(MapEditorState* state) {
	delete this->state;
	this->state = state;
}