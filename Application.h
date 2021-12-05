#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include "Camera.h"
#include "Editor.h"

class Application {
public:
	Application();
	~Application();

	void run();
	void update();
	void render();

private: 
	sf::RenderWindow* window;
	bool is_running;
	sf::Event event;

	Camera camera;
	Editor editor;
};

#endif