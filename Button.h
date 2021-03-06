#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>

enum button_states{ BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

// ?????????? ?? ????? ?????????? ?????? ???????? ??????????, ?????? ???????? ????? New

class Button : public sf::Drawable
{
public:
	Button();

	Button(float widht, float height, float posX, float posY, std::string buttonText);
	Button(float widht, float height, float posX, float posY, std::string buttonText, bool hide_shape);
	Button(float widht, float height, float posX, float posY, std::string buttonText, unsigned int letters_size);


	bool isClicked();
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f postion);

	void setTextColor(std::string sost, sf::Color color);
	void setShapeColor(std::string sost, sf::Color color);

	sf::RectangleShape* getShape();
	sf::Text* getText();

	void update(sf::Vector2f pos, sf::Event& event);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private: 
	
	bool shape_is_hide;

	short unsigned state;

	float widht;
	float height;
	float posX;
	float posY;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color shapeIdleColor;
	sf::Color shapeHoverColor;
	sf::Color shapeActiveColor;

	std::string buttonText;

	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	bool canPlaySound;

};
#endif