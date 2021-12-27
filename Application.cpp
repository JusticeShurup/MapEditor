#include "Application.h"
#include <iostream>

Application::Application() :
	camera(1920 / 2, 1920 / 2, 1920, 1080)
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "YaroslaveMapEditor");
	window->setView(camera.getView());
	
	is_running = false;
	editor = new Editor(window, &event, &camera);
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
	camera.update(event);
	window->setView(camera.getView());
	editor->update(camera);
}

void Application::render() {
	window->clear();
	editor->render();
	window->display();
}