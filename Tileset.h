#ifndef _TILESET_H_
#define _TILESET_H_
#include <SFML/Graphics.hpp>
class Tileset : public sf::Drawable
{
public: 
	Tileset();
	Tileset(sf::Vector2f position);
	Tileset(std::string filename, std::string sign, sf::Vector2f position);
	Tileset(sf::Texture* texture, std::string sign, sf::Vector2f position);

	void setTexture(std::string filename);
	void setTexture(sf::Texture* texture);
	sf::Texture* getTexture();


	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);

	void setSign(std::string sign);
	std::string getSign();

	sf::Vector2f getPosition();

	sf::RectangleShape* getShape();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private: 
	static const int WIDHT = 32;
	static const int HEIGHT = 32;
	sf::RectangleShape *shape;

	sf::Vector2f size;
	
	sf::Texture* texture;
	std::string sign;
};
#endif 