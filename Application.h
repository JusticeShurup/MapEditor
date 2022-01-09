#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "Camera.h"
#include "Editor.h"
#include "Menu.h"

class Application {
public:
	Application();
	~Application();

	Editor* getEditor();
	void setPause(bool pause);
	void close();

	void run();
	void update();
	void render();

	friend class Menu;
private: 
	sf::RenderWindow* window;
	sf::ContextSettings settings;

	bool is_running;
	bool active;
	bool pause; 
	sf::Event event;
	sf::Clock clock;

	Camera camera;
	Editor* editor;
	Menu* menu;
};
#endif