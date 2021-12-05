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

	sf::Texture* getTexture(std::string sign);

	std::vector<sf::Texture*> getTextures();
	std::vector<std::string> getSigns();

private: 
	TextureContainer();
	std::map<std::string, sf::Texture*> alphabet_textures; // sign - texture
	std::vector<std::string> signs;
	std::vector<sf::Texture*> textures;

	static TextureContainer* instance;
};
#endif

