#include "Button.h"

using namespace sf;

Button::Button() {}

Button::Button(float widht, float height, float posX, float posY, std::string name) 
	: widht(widht), height(height), posX(posX), posY(posY), buttonText(name) 
{

	state = BTN_IDLE;
	shape = RectangleShape(Vector2f(widht, height));
	shape.setPosition(Vector2f(posX, posY));
	shape.setOutlineThickness(5);

	font.loadFromFile("Inconsolata_Condensed-Bold.ttf");

	text.setFont(font);
	text.setCharacterSize(75);
	text.setFillColor(Color::Black);
	text.setString(name);
	text.setPosition(shape.getPosition().x + ((shape.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2)),
					 shape.getPosition().y);
}

Button::Button(float widht, float height, float posX, float posY, std::string name, unsigned int letters_size)
	: widht(widht), height(height), posX(posX), posY(posY), buttonText(name)
{

	state = BTN_IDLE;
	shape = RectangleShape(Vector2f(widht, height));
	shape.setPosition(Vector2f(posX, posY));
	shape.setOutlineThickness(5);

	font.loadFromFile("Inconsolata_Condensed-Bold.ttf");

	text.setFont(font);
	text.setCharacterSize(letters_size);
	text.setFillColor(Color::Black);
	text.setString(name);
	text.setPosition(shape.getPosition().x + ((shape.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2)),
					 shape.getPosition().y);
}

bool Button::isClicked() {
	if (state == BTN_ACTIVE) {
		return true; 
	}
	else return false;
}

void Button::setPosition(float x, float y) {
	shape.setPosition(x, y);
	text.setPosition(x, y);

}

void Button::setPosition(sf::Vector2f position) {
	shape.setPosition(position);
	text.setPosition(position.x + ((shape.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2)),
					 position.y);
}

sf::Text Button::getText() {
	return text;
}

void Button::update(Vector2f pos, Event& event) {
	state = BTN_IDLE;
	//Hover
	if (shape.getGlobalBounds().contains(pos) || text.getGlobalBounds().contains(pos))
	{
		state = BTN_HOVER;
		//Pressed
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			state = BTN_ACTIVE;
		}
	}

	switch (state)
	{
	case BTN_IDLE:
		this->shape.setFillColor(Color::White);
		this->shape.setOutlineThickness(0);
		this->text.setFillColor(Color::Black);
		this->shape.setOutlineColor(Color::White);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(Color::White);
		this->shape.setOutlineThickness(5);
		this->shape.setFillColor(Color::Green);
		this->text.setFillColor(Color::Red);
		this->shape.setOutlineColor(Color(127, 127, 127));
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(Color::White);
		this->text.setFillColor(Color::Red);
		this->shape.setOutlineColor(Color(127, 127, 127));
		break;

	default:
		this->shape.setFillColor(Color::White);
		this->text.setFillColor(Color::Black);
		this->shape.setOutlineColor(Color::White);
		break;
	}
}

void Button::draw(RenderTarget& target, RenderStates states) const {
	target.draw(text);
}

