#include "Camera.h"
#include <iostream>

Camera::Camera(float x, float y, float widht, float height) {
	view = sf::View(sf::FloatRect(x, y, widht, height));
	center = sf::Vector2f(x, y);
	size = sf::Vector2f(widht, height);
	view.setSize(500, 500);
	zoom_coefficient = 1;
}

Camera::~Camera() {}

sf::View& Camera::getView() {
	return view;
}

void Camera::update(sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		center.y += -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		center.y += 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		center.x += -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		center.x += 1;
	}
	view.setCenter(center);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
		view.zoom(1.001);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
		view.zoom(0.999);
	}

}

void Camera::setCenter(float x, float y) {
	center = sf::Vector2f(x, y);
	view.setCenter(x, y);
}

void Camera::setCenter(sf::Vector2f center) {
	this->center = center;
	view.setCenter(center);
}

void Camera::setSize(float x, float y) {
	size = sf::Vector2f(x, y);
	view.setSize(x, y);
}

void Camera::setSize(sf::Vector2f size) {
	this->size = size;
	view.setSize(size);
}

