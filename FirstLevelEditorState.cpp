#include "FirstLevelEditorState.h"
#include "Editor.h"
#include <iostream>

FirstLevelEditorState::FirstLevelEditorState(Editor* editor) : MapEditorState(editor) {
	editor->tilesets.clear();
	initWindow();
}

FirstLevelEditorState::~FirstLevelEditorState() {
}

void FirstLevelEditorState::initWindow() {
	for (int i = 0; i < 40; i++) {
		std::vector<Tileset> tileset;
		for (int j = 0; j < 50; j++) {
			std::string link;
			std::string sign = editor->map[i][j];
			int sost = sign[sign.size() - 1] - '0';
			sign = sign.substr(0, sign.size() - 2);
			tileset.emplace_back(Tileset(TextureContainer::getInstance()->getTilesetTexture(sign, sost), sign, sf::Vector2f(32, 32), sf::Vector2f(j * 34 + 5, i * 34 + 5), sost));
			tileset[j].setTempTexture(TextureContainer::getInstance()->getTilesetTexture(sign, sost));
		}
		editor->tilesets.push_back(tileset);
	}
}

void FirstLevelEditorState::update(Camera& camera, float delta_time) {
	float x = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window)).x;
	float y = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window)).y;

	editor->can_set_tileset = !editor->tilesets_menu.contains(sf::Vector2f(x, y));
	editor->tilesets_menu.update(*editor->event, camera, sf::Vector2f(x, y));
	editor->can_set_tileset ? editor->time_last_opening += delta_time : editor->time_last_opening = 0;
	!(*editor->pause) ? editor->time_last_opening += delta_time : editor->time_last_opening = 0;


	if (editor->event->type == sf::Event::KeyReleased) {
		if (editor->event->key.code == sf::Keyboard::Left) editor->rotateCurrentTileset(-1);
		else if (editor->event->key.code == sf::Keyboard::Right) editor->rotateCurrentTileset(1);
		editor->event->type = sf::Event::MouseMoved;
	}

	int i = 0;
	int j = 0;
	for (auto& t : editor->tilesets) {
		j = 0;
		for (auto& tileset : t) {
			if (tileset.getShape()->getGlobalBounds().contains(x, y)) {
				tileset.getShape()->setOutlineThickness(2);
				tileset.setTexture(editor->current_tileset->getTexture());
				if (editor->time_last_opening > 0.1) { // TO FIX BAG (Close menu, but after that tileset installed immediately)
					if ((editor->event->type == editor->event->MouseButtonReleased && editor->event->mouseButton.button == sf::Mouse::Left || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && editor->can_set_tileset) {
						if (tileset.getSign() != editor->current_tileset->getSign()) {
							tileset.setTempTexture(editor->current_tileset->getTexture());
							tileset.setSign(editor->current_tileset->getSign());
							editor->map[i][j] = editor->current_tileset->getSign() + "S" + std::to_string(int(editor->current_tileset->getSost()));
							updateFile();
						}
					}
					else if (editor->event->type == editor->event->MouseButtonReleased && editor->event->mouseButton.button == sf::Mouse::Right || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && editor->can_set_tileset) {
						if (tileset.getSign() != "snowS1") {
							tileset.setTempTexture(TextureContainer::getInstance()->getTilesetTexture("snow", 1));
							tileset.setSign("snowS1");
							editor->map[i][j] = "snowS1";
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

void FirstLevelEditorState::render() {
	for (auto& i : editor->tilesets) {
		for (auto& tileset : i) {
			editor->window->draw(tileset);
		}
	}

	if (!editor->camera->getIsZoomed()) editor->window->draw(editor->tilesets_menu);
}

void FirstLevelEditorState::updateFile() {
	std::ofstream f("Map.txt", std::ios_base::trunc);
	f.clear();
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 50; j++) {
			f << editor->map[i][j] << " ";
		}
		f << "\n";
	}
	f.close();
}