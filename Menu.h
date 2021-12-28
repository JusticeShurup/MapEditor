#ifndef _MENU_H_
#define _MENU_H_

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "MenuMainState.h"

class Application;

class Menu : public sf::Drawable
{
public:
	Menu(Application* application);
	
	void setNewMenuState(MenuState* menu_state);
	Application* getApplication();

	void update(sf::Event& event, sf::Vector2f mouse_pos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	MenuState* menu_state;
	Application* application;
};
#endif
