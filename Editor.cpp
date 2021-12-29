#include "Editor.h"
#include <fstream>
#include <iostream>
#include <string>

Editor::Editor()
	: tilesets_menu(TilesetsMenu(sf::Vector2f(1920/3, 1080), sf::Vector2f(0, 0), currentTileset)), 
	  camera(new Camera(1920/2, 1920/2, 1000, 1000))
{}

Editor::Editor(sf::RenderWindow* window, sf::Event *event, Camera* camera, bool* pause) :
	tilesets_menu(TilesetsMenu(sf::Vector2f(1920/3, 1080), sf::Vector2f(0, 0), currentTileset)),
	camera(camera), 
	pause(pause)
{
	time_last_opening = 0;
	can_set_tileset = true;
	currentTileset = new Tileset();
	textureContainer = TextureContainer::getInstance();
	this->window = window;
	this->event = event;
	initMap();
	initWindow();

	currentTileset->setImage(TextureContainer::getInstance()->getTexture("a", 1));
	currentTileset->setTexture(TextureContainer::getInstance()->getLink("a"));
	currentTileset->setSign(TextureContainer::getInstance()->getSigns()[1]);
	currentTileset->getShape()->setSize(sf::Vector2f(64, 64));

	tilesets_menu.setCurrentTileset(currentTileset);
}

Editor::~Editor(){}

void Editor::initWindow(){
	for (int i = 0; i < 40; i++) {
		std::vector<Tileset> tileset;
		for (int j = 0; j < 50; j++) {
			std::string link;
			std::string sign = map[i][j];
			int sost = sign[sign.size()-1] - '0';
			sign = sign.substr(0, sign.size()-2);
			tileset.emplace_back(Tileset(TextureContainer::getInstance()->getTexture(sign, sost), sign, sf::Vector2f(32, 32), sf::Vector2f(j * 34 + 5, i * 34 + 5), sost));
			tileset[j].setTempTexture(TextureContainer::getInstance()->getTexture(sign, sost));
		}
		tilesets.push_back(tileset);
	}
}

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

void Editor::initPalette() {
}

void Editor::rotateCurrentTileset(int8_t direction) {
	if (direction > 0) {
		currentTileset->setSost(currentTileset->getSost() + 1);
		currentTileset->setTexture(TextureContainer::getInstance()->getTexture(currentTileset->getSign(),
			currentTileset->getSost()));
	}
	else {
		currentTileset->setSost(currentTileset->getSost() - 1);
		currentTileset->setTexture(TextureContainer::getInstance()->getTexture(currentTileset->getSign(),
			currentTileset->getSost()));
	}

}

void Editor::update(Camera& camera, float delta_time){
	float x = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
	float y = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;

	can_set_tileset = !tilesets_menu.contains(sf::Vector2f(x, y));
	tilesets_menu.update(*event, camera, sf::Vector2f(x, y));
	can_set_tileset ? time_last_opening += delta_time : time_last_opening = 0;
	!(*pause) ? time_last_opening += delta_time : time_last_opening = 0;


	if (event->type == sf::Event::KeyReleased) {
		if (event->key.code == sf::Keyboard::Left) rotateCurrentTileset(-1);
		else if (event->key.code == sf::Keyboard::Right) rotateCurrentTileset(1);
		event->type = sf::Event::MouseMoved;
	}

	int i = 0;
	int j = 0;
	for (auto& t : tilesets) {
		j = 0;
		for (auto& tileset : t) {
			if (tileset.getShape()->getGlobalBounds().contains(x, y)) {
				tileset.getShape()->setOutlineThickness(2);
				tileset.setTexture(currentTileset->getTexture());
				if (time_last_opening > 0.1) { // TO FIX BAG (Close menu, but after that tileset installed immediately)
					if ((event->type == event->MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && can_set_tileset) {
						if (tileset.getSign() != currentTileset->getSign()) {
							tileset.setTempTexture(currentTileset->getTexture());
							tileset.setSign(currentTileset->getSign());
							map[i][j] = currentTileset->getSign() + "S" + std::to_string(int(currentTileset->getSost()));
							updateFile();
						}
					}
					else if (event->type == event->MouseButtonReleased && event->mouseButton.button == sf::Mouse::Right || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && can_set_tileset) {
						if (tileset.getSign() != "snowS1") {
							tileset.setTempTexture(TextureContainer::getInstance()->getTexture("snow", 1));
							tileset.setSign("snowS1");
							map[i][j] = "snowS1";
							updateFile();
						}
					}
				}
			}
			else {
				tileset.setTexture(tileset.getTempTexture());
				tileset.getShape()->setOutlineThickness(0);
			}
			j++;
		}
		i++;
	}
}

void Editor::updateFile() {
	std::ofstream f("Map.txt", std::ios_base::trunc);
	f.clear();
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 50; j++) {
			f << map[i][j] << " ";
		}
		f << "\n";
	}
	f.close();
}

void Editor::render() {
	for (auto& i : tilesets) {
		for (auto& tileset : i) {
			window->draw(tileset);
		}
	}

	if(!camera->getIsZoomed()) window->draw(tilesets_menu);
}