#include "Application.h"
#include <iostream>

Application::Application() :
	camera(100, 100, 100, 100)
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "YaroslaveMapEditor");
	window->setView(camera.getView());
	
	is_running = false;
	editor = Editor(window, &event);
}

Application::~Application() {}

void Application::run() {
	is_running = true;
	while (is_running) {
		update();
		render();
	}
}

void Application::update() {
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			is_running = false;
			window->close();
		}
	}
	editor.update();
	camera.update(event);
	window->setView(camera.getView());
}

void Application::render() {
	window->clear();
	editor.render();
	window->display();
}