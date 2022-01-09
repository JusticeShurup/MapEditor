#include "MenuMainState.h"
#include "Application.h"
#include "Menu.h"
#include "FirstLevelEditorState.h"
#include "SecondLevelEditorState.h"

MenuMainState::MenuMainState(Menu* menu) : MenuState(menu) {
	font.loadFromFile("Fonts/Roboto-Bold.ttf");

	title = new sf::Text;
	
	title->setString("Yaroslave Map Editor");
	title->setCharacterSize(75);
	title->setColor(sf::Color(128, 128, 128));
	title->setFont(font);
	title->setOutlineThickness(2);
	title->setOutlineColor(sf::Color::White);
	title->setPosition(1920 / 2 - title->getGlobalBounds().width / 2, 0);

	edit_frstlevel_button = new Button(300, 100, 300, 100, "Edit first level", true);
	edit_frstlevel_button->setTextColor("idle", sf::Color(128, 128, 128));
	edit_frstlevel_button->setTextColor("hover", sf::Color(200, 200, 200));
	edit_frstlevel_button->getText()->setCharacterSize(60);
	edit_frstlevel_button->setPosition(1920 / 2 - edit_frstlevel_button->getText()->getGlobalBounds().width / 3, 350);

	edit_scndlevel_button = new Button(300, 100, 1920 / 2 - 300, 1080 / 2 + 100, "Edit second level", true);
	edit_scndlevel_button->setTextColor("idle", sf::Color(128, 128, 128));
	edit_scndlevel_button->setTextColor("hover", sf::Color(200, 200, 200));
	edit_scndlevel_button->getText()->setCharacterSize(60);
	edit_scndlevel_button->setPosition(1920 / 2 - edit_frstlevel_button->getText()->getGlobalBounds().width / 3, 500);

	exit_button = new Button(300, 100, 1920 / 2 - 300 / 2, 1080 / 2 + 500, "Exit", true);
	exit_button->setTextColor("idle", sf::Color(128, 128, 128));
	exit_button->setTextColor("hover", sf::Color(200, 200, 200));
	exit_button->getText()->setCharacterSize(60);
	exit_button->setPosition(1920 / 2 - exit_button->getText()->getGlobalBounds().width - 50, 900);
}

MenuMainState::~MenuMainState() {
	delete title; 

	delete edit_frstlevel_button;
	delete edit_scndlevel_button;

	delete exit_button;
}

void MenuMainState::update(sf::Event& event, sf::Vector2f mouse_pos){
	Editor* editor = menu->getApplication()->getEditor();
	edit_frstlevel_button->update(mouse_pos, event);
	edit_scndlevel_button->update(mouse_pos, event);
	exit_button->update(mouse_pos, event);

	if (edit_frstlevel_button->isClicked()) {	
		menu->getApplication()->setPause(false);
		editor->setNewState(new FirstLevelEditorState(editor));
	}
	else if (edit_scndlevel_button->isClicked()) {
		menu->getApplication()->setPause(false);
		editor->setNewState(new SecondLevelEditorState(editor));
	}
	else if (exit_button->isClicked()) {
		menu->getApplication()->close();
	}
}

void MenuMainState::draw(sf::RenderTarget& target) {
	target.draw(*title);
	target.draw(*edit_frstlevel_button);
	target.draw(*edit_scndlevel_button);
	target.draw(*exit_button);
}