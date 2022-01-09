#include "Application.h"
#include <iostream>

Application::Application() :
	camera(1920 / 2, 1920 / 2, 1920, 1080)
{
	settings.antialiasingLevel = 10;
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "YaroslaveMapEditor", sf::Style::Default, settings);
	window->setView(camera.getView());
	
	is_running = false;
	editor = new Editor(window, &event, &camera, &pause);
	menu = new Menu(this);
	active = true;
	pause = true;
}

Application::~Application() {
	delete window;
	delete editor;
}

Editor* Application::getEditor() {
	return editor;
}

void Application::setPause(bool pause) {
	this->pause = pause;
}

void Application::close() {
	is_running = false;
}

void Application::run() {
	is_running = true;
	while (is_running) {
		update();
		render();
	}
	window->close();
}

void Application::update() {
	float delta_time = clock.restart().asSeconds();
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			is_running = false;
			window->close();
		}
		if (event.type == sf::Event::LostFocus) {
			active = false;
		}
		else if (event.type == sf::Event::GainedFocus) {
			active = true;
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape) {
				pause = !pause;
			}
		}
	}	
	if (active && !pause) {
		camera.update(event, delta_time);
		window->setView(camera.getView());
		editor->update(camera, delta_time);
	}
	else if (active) {
		camera.setSize(1920, 1080);
		camera.getView().setCenter(1920 / 2, 1080 / 2);
		window->setView(camera.getView());
		menu->update(event, sf::Vector2f(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x, window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y));
	}
}

void Application::render() {
	window->clear();
	if (!pause) editor->render();
	else window->draw(*menu);
	window->display();
}