#include "MenuMainState.h"
#include "Application.h"
#include "Menu.h"


MenuMainState::MenuMainState(Menu* menu) : MenuState(menu) {
	font.loadFromFile("Fonts/Roboto-Bold.ttf");

	title = new sf::Text;
	
	title->setString("Yaroslave Map Editor");
	title->setCharacterSize(60);
	title->setColor(sf::Color(128, 128, 128));
	title->setFont(font);
	title->setOutlineThickness(2);
	title->setOutlineColor(sf::Color::White);
	title->setPosition(1920 / 2 - title->getGlobalBounds().width / 2, 0);

	edit_frstlevel_button = new Button(300, 100, 0, 0, "Edit first level");
	edit_frstlevel_button->setColor(sf::Color(128, 128, 128));
	edit_frstlevel_button->setPosition(1920 / 2 - edit_frstlevel_button->getText().getGlobalBounds().width / 2, 200);

	edit_scndlevel_button = new Button(300, 100, 1920 / 2 - 300 / 2, 1080 / 2 + 100, "Edit second level");
	edit_scndlevel_button->setColor(sf::Color(128, 128, 128));
	edit_scndlevel_button->setPosition(1920 / 2 - edit_scndlevel_button->getText().getGlobalBounds().width / 2, 400);

	exit_button = new Button(300, 100, 1920 / 2 - 300 / 2, 1080 / 2 + 500, "Exit");
	exit_button->setColor(sf::Color(128, 128, 128));
	exit_button->setPosition(1920 / 2 - exit_button->getText().getGlobalBounds().width / 2, 700);
}

MenuMainState::~MenuMainState() {
	delete title; 

	delete edit_frstlevel_button;
	delete edit_scndlevel_button;

	delete exit_button;
}

void MenuMainState::update(sf::Event& event, sf::Vector2f mouse_pos){
	edit_frstlevel_button->update(mouse_pos, event);
	edit_scndlevel_button->update(mouse_pos, event);
	exit_button->update(mouse_pos, event);

	if (edit_frstlevel_button->isClicked()) menu->getApplication()->setPause(false);
	if (exit_button->isClicked()) menu->getApplication()->close();
}

void MenuMainState::draw(sf::RenderTarget& target) {
	target.draw(*title);
	target.draw(*edit_frstlevel_button);
	target.draw(*edit_scndlevel_button);
	target.draw(*exit_button);
}