#include "GameObjectsMenuMainState.h"

#include "GameObjectsMenu.h"
#include "GameObjectsMenuPaletteState.h"
#include "Button.h"

GameObjectsMenuMainState::GameObjectsMenuMainState(GameObjectsMenu* gameobjs_menu, GameObject* current_gameobj) : GameObjectsMenuState(gameobjs_menu, current_gameobj) {
	buttons = std::vector<Button*>({});
	buttons.push_back(new Button(550, 75, -100000, -100000, "Buildings", false));
	buttons[0]->setShapeColor("idle", sf::Color(145, 94, 96));
	buttons[0]->setShapeColor("hover", sf::Color::Red);
	buttons[0]->setTextColor("hover", sf::Color::White);
	buttons.push_back(new Button(550, 75, -10000, -10000, "Fixtures", false));
	buttons[1]->setShapeColor("idle", sf::Color(145, 94, 96));
	buttons[1]->setShapeColor("hover", sf::Color::Red);
	buttons[1]->setTextColor("hover", sf::Color::White);

	main_texture = new sf::Texture;
	main_texture->loadFromFile("main_tilesetmenu.png");

	gameobjs_menu->getBackground()->setTexture(main_texture);
}

GameObjectsMenuMainState::~GameObjectsMenuMainState() {
	delete main_texture;
	for (auto button : buttons) {
		delete button;
	}
}


void GameObjectsMenuMainState::update(sf::Event& event, Camera& camera, sf::Vector2f mouse_pos) {
	sf::Vector2f position(camera.getView().getCenter().x - camera.getView().getSize().x / 2,
						  camera.getView().getCenter().y - camera.getView().getSize().y / 2);

	current_gameobj->setPosition(mouse_pos);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->setPosition(position.x + gameobjs_menu->getGlobalBounds().width / 2 - buttons[i]->getShape()->getGlobalBounds().width / 2 + 5,
			position.y + buttons[i]->getText()->getGlobalBounds().height + 100 * (i + 1));
		buttons[i]->update(mouse_pos, event);
		if (buttons[i]->isClicked()) {
			gameobjs_menu->setGameObjectsMenuState(new GameObjectsMenuPaletteState(gameobjs_menu, buttons[i]->getText()->getString(), current_gameobj));
			break;
		}
	}
}

void GameObjectsMenuMainState::render(sf::RenderTarget& target) {
	for (auto button : buttons) {
		target.draw(*button);
	}
}