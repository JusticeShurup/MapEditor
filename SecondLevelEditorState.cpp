#include "SecondLevelEditorState.h"
#include "Editor.h"
#include <iostream>

SecondLevelEditorState::SecondLevelEditorState(Editor* editor) : MapEditorState(editor) {
	editor->tilesets.clear();
	editor->gameobjects.clear();


	editor->current_gameobj->showObjectOutlines();
	editor->current_gameobj->showHitboxOutlines();
	delete_state = false;
	time_after_click = 0;
	initWindow();
}

SecondLevelEditorState::~SecondLevelEditorState() {
}

void SecondLevelEditorState::initWindow() {
	for (int i = 0; i < 40; i++) {
		std::vector<Tileset> tileset;
		for (int j = 0; j < 50; j++) {
			std::string link;
			std::string sign = editor->map[i][j];
			int sost = sign[sign.size() - 1] - '0';
			sign = sign.substr(0, sign.size() - 2);
			tileset.emplace_back(Tileset(TextureContainer::getInstance()->getTilesetTexture(sign, sost), sign, sf::Vector2f(32, 32), sf::Vector2f(j * 32, i * 32), sost));
			tileset[j].setTempTexture(TextureContainer::getInstance()->getTilesetTexture(sign, sost));
		}
		editor->tilesets.push_back(tileset);
	}
	std::ifstream file("GameObjectsMap.txt");
	while (!file.eof()) {
		std::string gameobj_name;
		float obj_width = 0, obj_height = 0, obj_posx = 0, obj_posy = 0, hitbox_width = 0, hitbox_height = 0, hitbox_posx = 0, hitbox_posy = 0;
		file >> gameobj_name >> obj_width >> obj_height >> obj_posx >> obj_posy >> hitbox_width >> hitbox_height >> hitbox_posx >> hitbox_posy;
		std::cout << gameobj_name << " " << obj_width << " " << obj_height << std::endl;
		editor->gameobjects.push_back(GameObject(TextureContainer::getInstance()->getGameObjectTexture(gameobj_name), 
			sf::Vector2f(obj_width, obj_height), sf::Vector2f(obj_posx, obj_posy), sf::Vector2f(hitbox_width, hitbox_height), sf::Vector2f(hitbox_posx, hitbox_posy), gameobj_name));
	}
	file.close();
}

void SecondLevelEditorState::update(Camera& camera, float delta_time) {
	float x = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window)).x;
	float y = editor->window->mapPixelToCoords(sf::Mouse::getPosition(*editor->window)).y;

	editor->gameobjs_menu.update(*editor->event, camera, sf::Vector2f(x, y));

	editor->current_gameobj->setPosition(x, y);

	editor->can_set_tileset = !editor->gameobjs_menu.contains(sf::Vector2f(x, y));
	editor->tilesets_menu.update(*editor->event, camera, sf::Vector2f(x, y));
	editor->can_set_tileset ? editor->time_last_opening += delta_time : editor->time_last_opening = 0;
	!(*editor->pause) ? editor->time_last_opening += delta_time : editor->time_last_opening = 0;

	if (editor->event->type == sf::Event::KeyReleased && editor->event->key.code == sf::Keyboard::R) {
		delete_state = !delete_state;
		editor->event->type = sf::Event::TouchEnded;
	}

	if (!delete_state) {
		if (editor->time_last_opening > 0.1) {
			if (!editor->gameobjs_menu.contains(sf::Vector2f(x, y))) {
				if (editor->event->type == editor->event->MouseButtonReleased && editor->event->mouseButton.button == sf::Mouse::Left) {
					GameObject* g = editor->current_gameobj;
					editor->gameobjects.emplace_back(GameObject(TextureContainer::getInstance()->getGameObjectTexture(g->getName()), g->getObjectShape()->getSize(), g->getObjectPosition(), g->getHitboxShape()->getSize(), g->getHitboxPosition(), g->getName()));
					updateFile();
					editor->event->type = sf::Event::TouchEnded;
					time_after_click = 0;
				}
			}
		}
	}
	else {
		for (int i = 0; i < editor->gameobjects.size(); i++) {
			if (editor->gameobjects[i].getObjectShape()->getGlobalBounds().contains(x, y)) {
				editor->gameobjects[i].getObjectShape()->setOutlineThickness(5);
				editor->gameobjects[i].getHitboxShape()->setOutlineThickness(3);
				editor->gameobjects[i].hideHitbox(false);
				if (editor->event->type == editor->event->MouseButtonReleased && editor->event->mouseButton.button == sf::Mouse::Left) {
					editor->gameobjects.erase(editor->gameobjects.begin() + i);
					updateFile();
				}
			}
			else {
				editor->gameobjects[i].getObjectShape()->setOutlineThickness(0);
				editor->gameobjects[i].getHitboxShape()->setOutlineThickness(0);
				editor->gameobjects[i].hideHitbox(true);
			}
		}
	}
	time_after_click += delta_time;

	
	/*
	int i = 0;
	int j = 0;
	for (auto& g : editor->gameobjects) {
		j = 0;
		for (auto& gameobj : g) {
			if (gameobj.getObjectShape()->getGlobalBounds().contains(x, y)) {
				gameobj.showObjectOutlines();
				if (editor->time_last_opening > 0.1) { // TO FIX BAG (Close menu, but after that tileset installed immediately)
					if ((editor->event->type == editor->event->MouseButtonReleased && editor->event->mouseButton.button == sf::Mouse::Left || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && editor->can_set_tileset) {
						if (tileset.getSign() != editor->current_tileset->getSign()) {
							tileset.setTempTexture(editor->current_tileset->getTexture());
							tileset.setSign(editor->current_tileset->getSign());
							editor->map[i][j] = editor->current_tileset->getSign() + "S" + std::to_string(int(editor->current_tileset->getSost()));
							editor->updateFile();
						}
					}
					else if (editor->event->type == editor->event->MouseButtonReleased && editor->event->mouseButton.button == sf::Mouse::Right || sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && editor->can_set_tileset) {
						if (tileset.getSign() != "snowS1") {
							tileset.setTempTexture(TextureContainer::getInstance()->getTexture("snow", 1));
							tileset.setSign("snowS1");
							editor->map[i][j] = "snowS1";
							editor->updateFile();
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
	*/
}

void SecondLevelEditorState::render() {
	for (auto& i : editor->tilesets) {
		for (auto& tileset : i) {
			editor->window->draw(tileset);
		}
	}
	for (auto& g : editor->gameobjects) {
		editor->window->draw(g);
	}
	if(!delete_state)editor->window->draw(*editor->current_gameobj);
	if (!editor->camera->getIsZoomed()) editor->window->draw(editor->gameobjs_menu);
}

void SecondLevelEditorState::updateFile() {
	std::ofstream f("GameObjectsMap.txt", std::ios_base::trunc);
	f.clear();
	for (auto& g : editor->gameobjects) {
		f << g.getName() << " " << g.getObjectShape()->getSize().x << " " << g.getObjectShape()->getSize().y  << " " << g.getObjectPosition().x << " " << g.getObjectPosition().y << " " << g.getHitboxShape()->getSize().x << " " << g.getHitboxShape()->getSize().y << " " << g.getHitboxPosition().x << " " << g.getHitboxPosition().y << "\n";
	}
	f.close();
}