#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
class Camera
{
public:
	Camera(float center_x, float center_y, float size_widht, float size_height);
	~Camera();
	sf::View& getView();

	void update(sf::Event& event);

	void setCanZoom(bool can_zoom);
	bool getIsZoomed();

	void setCenter(float x, float y);
	void setCenter(sf::Vector2f center);
	void setSize(float x, float y);
	void setSize(sf::Vector2f size);

private:
	sf::View view;

	sf::Vector2f size;
	sf::Vector2f center;
	float zoom_coefficient;

	bool can_zoom;
	bool is_zoomed;
};
#endif