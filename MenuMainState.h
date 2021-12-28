#ifndef _MENU_MAIN_STATE_H_
#define _MENU_MAIN_STATE_H_
#include "MenuState.h"
#include "Button.h"

class MenuMainState : public MenuState
{
public: 
	MenuMainState(Menu* menu);
	~MenuMainState();

	void update(sf::Event& event, sf::Vector2f mouse_pos) override;
	void draw(sf::RenderTarget& target);
private: 
	sf::Font font;
	sf::Text* title;

	Button* edit_frstlevel_button;
	Button* edit_scndlevel_button;

	Button* exit_button;

};
#endif
