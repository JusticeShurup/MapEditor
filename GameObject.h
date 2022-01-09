#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class GameObject : public sf::Drawable
{
public:
	GameObject(sf::Vector2f object_size, sf::Vector2f hitbox_size);
	GameObject(std::string filename, sf::Vector2f object_size, sf::Vector2f object_position, sf::Vector2f hitbox_size, sf::Vector2f hitbox_position, std::string name);
	GameObject(sf::Texture* texture, sf::Vector2f object_size, sf::Vector2f object_position, sf::Vector2f hitbox_size, sf::Vector2f hitbox_position, std::string name);
	~GameObject();

	sf::RectangleShape* getObjectShape();
	sf::RectangleShape* getHitboxShape();

	void setPosition(sf::Vector2f object_position);
	void setPosition(float object_x, float object_y);
	void setNewHitboxPosition(sf::Vector2f hitbox_position);

	sf::Vector2f getObjectPosition();
	sf::Vector2f getHitboxPosition();

	void showObjectOutlines();
	void showHitboxOutlines();
	
	void setTexture(std::string filename);
	void setTexture(sf::Texture* texture);
	sf::Texture* getTexture();

	void setName(std::string name);
	std::string getName();


	void hideHitbox(bool flag);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:	
	std::string name;

	sf::Texture* texture;

	sf::RectangleShape* object;

	sf::RectangleShape hitbox;
	sf::Vector2f hitbox_delta_position;

	bool is_load_from_file;
	bool is_hitbox_hidden;
};
#endif
