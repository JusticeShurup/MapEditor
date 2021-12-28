#ifndef _MENU_STATE_H_
#define _MENU_STATE_H_
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Menu;
class MenuState
{
protected :
	Menu* menu;
public: 
	MenuState(Menu* menu);

	virtual void update(sf::Event& event, sf::Vector2f mouse_pos) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
};
#endif