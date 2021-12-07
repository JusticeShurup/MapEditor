#include "Editor.h"
#include <fstream>
#include <iostream>
#include <string>

void printMap(char map[40][50]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 50; j++)
			std::cout << map[i][j];
		std::cout << std::endl;
	}
}

Editor::Editor(){}

Editor::Editor(sf::RenderWindow* window, sf::Event *event) 
{
	currentTileset = new Tileset();
	textureContainer = TextureContainer::getInstance();
	this->window = window;
	this->event = event;
	initMap();
	initWindow();
	initPalette();

	currentTileset->setImage(TextureContainer::getInstance()->getTexture("a"));
	currentTileset->setTexture(TextureContainer::getInstance()->getLink("a"));
	currentTileset->setSign(TextureContainer::getInstance()->getSigns()[1]);

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


			tileset.emplace_back(Tileset(TextureContainer::getInstance()->getTexture(sign, sost), sign, sf::Vector2f(j * 34 + 5, i * 34 + 5), sost));


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
		std::cout << std::endl;
		map.push_back(string);
	}
	f.close();
}

void Editor::initPalette() {
	std::vector<Tileset> tilesets;
	std::vector<sf::Texture*> textures = TextureContainer::getInstance()->getTextures();
	std::vector<std::string> signs = TextureContainer::getInstance()->getSigns();
	std::vector<std::string> links = TextureContainer::getInstance()->getLinks();

	for (int i = 0; i < textures.size(); i++) {
		tilesets.push_back(Tileset(links[i], signs[i], sf::Vector2f(i * -34 - 64, 5), 1));
	}

	tilesets_palette.push_back(tilesets);
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

void Editor::update(){
	
	float x = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
	float y = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;
	
	currentTileset->setPosition(x - currentTileset->getShape()->getGlobalBounds().width / 2,
								y - currentTileset->getShape()->getGlobalBounds().width / 2);

	if (event->type == sf::Event::KeyReleased) {
		if (event->key.code == sf::Keyboard::Left) rotateCurrentTileset(-1);
		else if (event->key.code == sf::Keyboard::Right) rotateCurrentTileset(1);
		currentTileset->setPosition(x - currentTileset->getShape()->getGlobalBounds().width / 2,
									y - currentTileset->getShape()->getGlobalBounds().width / 2);
		event->type = sf::Event::MouseMoved;
	}

	int i = 0;
	int j = 0;
	for (auto& t : tilesets) {
		j = 0;
		for (auto& tileset : t) {
			if (tileset.getShape()->getGlobalBounds().contains(x, y)) {
				tileset.getShape()->setOutlineThickness(2);
				if (event->type == event->MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					if (tileset.getSign() != currentTileset->getSign()) {
						tileset.setTexture(currentTileset->getTexture());
						tileset.setSign(currentTileset->getSign());
						map[i][j] = currentTileset->getSign() + "S" + std::to_string(int(currentTileset->getSost()));
						updateFile();
					}
				}
				else if (event->type == event->MouseButtonReleased && event->mouseButton.button == sf::Mouse::Right) {
					tileset.setTexture(nullptr);
				}
			}
			else {
				tileset.getShape()->setOutlineThickness(0);
			}
			j++;
		}
		i++;
	}

	for (auto& tilesets : tilesets_palette) {
		for (auto& tileset : tilesets) {
			if (tileset.getShape()->getGlobalBounds().contains(x, y)) {
				tileset.getShape()->setOutlineThickness(2);
				if (event->type == event->MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left) {
					currentTileset->setSost(1);
					currentTileset->setImage(TextureContainer::getInstance()->getTexture(tileset.getSign()));
					currentTileset->setTexture(TextureContainer::getInstance()->getLink(tileset.getSign()));
					currentTileset->setSign(tileset.getSign());
				}
			}
			else
			{
				tileset.getShape()->setOutlineThickness(0);
			}

		}
	}
			
}

void Editor::updateFile() {
	std::ofstream f("Map.txt", std::ios_base::trunc);
	f.clear();
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 50; j++) {
			f << map[i][j] << " ";
		}
		f << std::endl;
	}
	f.close();
}

void Editor::render() {
	for (auto& i : tilesets) {
		for (auto& tileset : i) {
			window->draw(tileset);
		}
	}
	for (auto& tilesets : tilesets_palette) {
		for (auto& tileset : tilesets) {
			window->draw(tileset);
		}
	}
	window->draw(*currentTileset);

}