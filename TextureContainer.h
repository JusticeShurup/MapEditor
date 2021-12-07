#ifndef _TEXTURE_CONTAINER_H_
#define _TEXTURE_CONTAINER_H_
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>

class TextureContainer
{
public:
	static TextureContainer* getInstance();

	sf::Image* getImage(std::string sign);
	
	sf::Texture* getTexture(std::string sign, uint8_t sost);

	sf::Texture* getTexture(std::string sign);
	std::string getLink(std::string sign);

	std::vector<sf::Texture*> getTextures();
	std::vector<std::string> getSigns();
	std::vector<std::string> getLinks();

	sf::Texture* rotateTexture(sf::Texture* texture);

private: 
	TextureContainer();

	std::map<std::string, sf::Image*> alphabet_images;
	std::map<std::string, sf::Texture*> alphabet_textures; // sign - texture

	std::map<std::string, std::map<uint8_t, sf::Texture*>> alphabet_textures1;

	std::map<std::string, std::string> alphabet_links;

	std::vector<sf::Image*> images;
	std::vector<std::string> signs;
	std::vector<sf::Texture*> textures;

	std::vector<std::vector<sf::Texture*>> textures1;

	std::vector<std::string> links;

	static TextureContainer* instance;
};
#endif

