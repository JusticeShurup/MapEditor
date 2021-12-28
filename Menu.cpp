#include "Menu.h"


Menu::Menu(Application* application) : application(application) {
	menu_state = new MenuMainState(this);
}

void Menu::setNewMenuState(MenuState* menu_state) {
	delete this->menu_state;

	this->menu_state = menu_state;
}

Application* Menu::getApplication() {
	return application;
}

void Menu::update(sf::Event& event, sf::Vector2f mouse_pos) {
	menu_state->update(event, mouse_pos);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	menu_state->draw(target);
}