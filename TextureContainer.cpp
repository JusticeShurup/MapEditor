#include "TextureContainer.h"
#include <string>
#include <iostream>

TextureContainer* TextureContainer::instance = nullptr;

TextureContainer::TextureContainer() {
	std::ifstream file("TilesetTextureAlphabet.txt");
	std::string sign;
	std::string filename;
	while (!file.eof()) {
		file >> sign >> filename;
		int tilesets_size = std::atoi(filename.c_str());
		std::string category_name = sign;
		
		std::map<std::string, std::map<uint8_t, sf::Texture*>> alphabet_textures_for_pallete;
		for (int i = 0; i < tilesets_size; i++) {
			file >> sign >> filename;

			sf::Image* image = new sf::Image;
			sf::Texture* texture = new sf::Texture;

			image->loadFromFile(filename);
			texture->loadFromFile(filename);

			alphabet_tilesets_images.emplace(sign, image);

			std::map<uint8_t, sf::Texture*> map;
			map[1] = texture;
			alphabet_tilesets_textures.emplace(sign, map);
			alphabet_textures_for_pallete.emplace(sign, map);

			for (int i = 2; i <= 4; i++) {
				alphabet_tilesets_textures[sign].emplace(i, rotateTexture(alphabet_tilesets_textures[sign][i - 1]));
				alphabet_textures_for_pallete[sign].emplace(i, rotateTexture(alphabet_textures_for_pallete[sign][i - 1]));
			}

			alphabet_tilesets_links.emplace(sign, filename);
			tilesets_signs.push_back(sign);
			tilesets_textures.push_back(texture);
			tilesets_links.push_back(filename);
		}
		alphabet_textures_tilesets_pallete.emplace(category_name, alphabet_textures_for_pallete);
	}
	file.close();
	file.open("GameObjectTextureAlphabet.txt");
	while (!file.eof()) {
		file >> sign >> filename;
		int gameobjects_size = std::atoi(filename.c_str());
		std::string category_name = sign;

		std::map<std::string, sf::Texture*> alphabet_texture_for_pallete;
		for (int i = 0; i < gameobjects_size; i++) {
			file >> sign >> filename; 
			float width = 0;
			float heigth = 0;

			file >> width >> heigth;
			gameobjects_native_size.emplace(sign, sf::Vector2f(width, heigth));
			file >> width >> heigth;
			gameobjects_hitbox_size.emplace(sign, sf::Vector2f(width, heigth));
			file >> width >> heigth;
			gameobjects_hitbox_position.emplace(sign, sf::Vector2f(width, heigth));

			sf::Image* image = new sf::Image;
			sf::Texture* texture = new sf::Texture;

			image->loadFromFile(filename);
			texture->loadFromFile(filename);

			alphabet_gameobjects_images.emplace(sign, image);
			alphabet_gameobjects_textures.emplace(sign, texture);
			alphabet_texture_for_pallete.emplace(sign, texture);

			alphabet_gameobjects_links.emplace(sign, filename);
			gameobjects_names.push_back(sign);
			gameobjects_textures.push_back(texture);
			gameobjects_links.push_back(filename);
		}
		alphabet_textures_gameobjects_pallete.emplace(category_name, alphabet_texture_for_pallete);
	}
	file.close();
}

//tilesets
sf::Texture* TextureContainer::getTilesetTexture(std::string sign, uint8_t sost) {
	if (sost < 1 || sost > 4) sost = 1;
	return alphabet_tilesets_textures[sign][sost];
}

std::string TextureContainer::getTilesetLink(std::string sign) {
	return alphabet_tilesets_links[sign];
}

std::vector<sf::Texture*> TextureContainer::getTilesetsTextures() {
	return tilesets_textures;
}

std::map<std::string, std::map<uint8_t, sf::Texture*>> TextureContainer::getTilesetsTexturesByCathegory(std::string cathegory_name){
	return alphabet_textures_tilesets_pallete[cathegory_name];
}

std::vector<std::string> TextureContainer::getTilesetsSigns() {
	return tilesets_signs;
}

std::vector<std::string> TextureContainer::getTilesetsLinks() {
	return tilesets_links;
}
//Tilesets

//GameObjects
sf::Texture* TextureContainer::getGameObjectTexture(std::string name) {
	return alphabet_gameobjects_textures[name];
}
std::string TextureContainer::getGameObjectLink(std::string name) {
	return alphabet_gameobjects_links[name];
}
std::vector<sf::Texture*> TextureContainer::getGameObjectTextures() {
	return gameobjects_textures;
}

std::map<std::string, sf::Texture*> TextureContainer::getGameObjectsTexturesByCathegory(std::string cathegory_name) {
	return alphabet_textures_gameobjects_pallete[cathegory_name];
}
std::vector<std::string> TextureContainer::getGameObjectsNames() {
	return gameobjects_names;
}
std::vector<std::string> TextureContainer::getGameObjectsLinks() {
	return gameobjects_links;
}

sf::Vector2f TextureContainer::getGameObjectNativeSize(std::string name) {
	return gameobjects_native_size[name];
}

sf::Vector2f TextureContainer::getGameObjectHitboxSize(std::string name) {
	return gameobjects_hitbox_size[name];
}

sf::Vector2f TextureContainer::getGameObjectHitboxPosition(std::string name) {
	return gameobjects_hitbox_position[name];
}
//GameObjects

sf::Texture* TextureContainer::rotateTexture(sf::Texture* texture) { 
	sf::Image image = texture->copyToImage();
	const sf::Uint8* pixels = image.getPixelsPtr();

	std::vector<std::vector<sf::Color>> texture_in_pixels;
	sf::Uint8* pix = new sf::Uint8[32 * 32 * 4];

	int count = 0;
	for (int i = 0; i < 32 * 32 * 4; i += 4) {
		pix[i] = pixels[(32 * 32 * 4 - 1) - (i + 3)];
		pix[i + 1] = pixels[(32 * 32 * 4 - 1) - (i + 2)];
		pix[i + 2] = pixels[(32 * 32 * 4 - 1) - (i + 1)];
		pix[i + 3] = 255;
		count++;
	}

	int y = 0;
	int x = 0;
	std::vector<sf::Color> matrix;
	for (int i = 0; i < 32 * 32 * 4; i += 4) {
		matrix.push_back(sf::Color(pix[i], pix[i + 1], pix[i + 2], pix[i + 3]));
		x++;
		if (x == 32) {
			x = 0;
			y++;
			texture_in_pixels.push_back(matrix);
			matrix.clear();
		}
	}

	int n = 32;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			sf::Color temp = texture_in_pixels[i][j];
			texture_in_pixels[i][j] = texture_in_pixels[j][i];
			texture_in_pixels[j][i] = temp;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n / 2; j++) {
			sf::Color temp = texture_in_pixels[i][n - j - 1];
			texture_in_pixels[i][n - j - 1] = texture_in_pixels[i][j];
			texture_in_pixels[i][j] = temp;
		}
	}

	y = 0;
	x = 0;
	for (int i = 0; i < 32 * 32 * 4; i += 4) {
		pix[i] = texture_in_pixels[y][x].r;
		pix[i + 1] = texture_in_pixels[y][x].g;
		pix[i + 2] = texture_in_pixels[y][x].b;
		pix[i + 3] = texture_in_pixels[y][x].a;
		x++;
		if (x == 32) {
			x = 0;
			y++;
		}
	}

	sf::Texture* texture_new = new sf::Texture;
	texture_new->create(32, 32);
	texture_new->update(pix);

	return texture_new;

	delete[] pix;
}

TextureContainer* TextureContainer::getInstance() {
	if (!TextureContainer::instance) {
		TextureContainer::instance = new TextureContainer;
	}
	return TextureContainer::instance;
}