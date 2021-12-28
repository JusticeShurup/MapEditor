#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "Camera.h"
#include "Editor.h"
#include "Menu.h"

class Application {
public:
	Application();
	~Application();

	void setPause(bool pause);
	void close();

	void run();
	void update();
	void render();

private: 
	sf::RenderWindow* window;
	bool is_running;
	bool active;
	bool pause; 
	sf::Event event;

	Camera camera;
	Editor* editor;
	Menu* menu;
};
#endif