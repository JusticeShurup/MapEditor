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

	// Tilesets
	sf::Texture* getTilesetTexture(std::string sign, uint8_t sost);
	std::string getTilesetLink(std::string sign);
	std::vector<sf::Texture*> getTilesetsTextures();
	std::map<std::string, std::map<uint8_t, sf::Texture*>> getTilesetsTexturesByCathegory(std::string category_name);
	std::vector<std::string> getTilesetsSigns();
	std::vector<std::string> getTilesetsLinks();
	//Tilesets

	//GameObjects
	sf::Texture* getGameObjectTexture(std::string name);
	std::string getGameObjectLink(std::string name);
	std::vector<sf::Texture*> getGameObjectTextures();
	std::map<std::string, sf::Texture*> getGameObjectsTexturesByCathegory(std::string cathegory_name);
	std::vector<std::string> getGameObjectsNames();
	std::vector<std::string> getGameObjectsLinks();
	sf::Vector2f getGameObjectNativeSize(std::string name);
	sf::Vector2f getGameObjectHitboxSize(std::string name);
	sf::Vector2f getGameObjectHitboxPosition(std::string name);
	//GameObjects

	sf::Texture* rotateTexture(sf::Texture* texture);

private: 
	TextureContainer();

	//Tilesets
	std::map<std::string, sf::Image*> alphabet_tilesets_images;
	std::map<std::string, std::map<std::string, std::map<uint8_t, sf::Texture*>>> alphabet_textures_tilesets_pallete;
	std::map<std::string, std::map<uint8_t, sf::Texture*>> alphabet_tilesets_textures;
	std::map<std::string, std::string> alphabet_tilesets_links;
	std::vector<sf::Image*> tilesets_images;
	std::vector<std::string> tilesets_signs;
	std::vector<sf::Texture*> tilesets_textures;
	std::vector<std::string> tilesets_links;
	//Tilesets

	//GameObjects
	std::map<std::string, sf::Image*> alphabet_gameobjects_images;
	std::map<std::string, std::map<std::string, sf::Texture*>> alphabet_textures_gameobjects_pallete;
	std::map<std::string, sf::Texture*> alphabet_gameobjects_textures; 
	std::map<std::string, std::string> alphabet_gameobjects_links;
	std::vector<sf::Image*> gameobjects_images;
	std::vector<std::string> gameobjects_names;
	std::vector<sf::Texture*> gameobjects_textures;
	std::vector<std::string> gameobjects_links;
	std::map<std::string, sf::Vector2f> gameobjects_native_size;
	std::map<std::string, sf::Vector2f> gameobjects_hitbox_size;
	std::map<std::string, sf::Vector2f> gameobjects_hitbox_position;
	//GameObjects

	static TextureContainer* instance;
};
#endif