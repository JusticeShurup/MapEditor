#include "TextureContainer.h"
#include <iostream>

TextureContainer* TextureContainer::instance = nullptr;

TextureContainer::TextureContainer() {
	std::ifstream file("TextureAlphabet.txt");
	std::string sign;
	std::string filename;
	while (file >> sign >> filename) {
		if (sign != "_") {
			sf::Texture *texture = new sf::Texture;
			texture->loadFromFile(filename);
			alphabet_textures.emplace(sign, texture);
			signs.push_back(sign);
			textures.push_back(texture);
		}
	}
	file.close();
}

sf::Texture* TextureContainer::getTexture(std::string sign) {
	return alphabet_textures[sign];
}

std::vector<sf::Texture*> TextureContainer::getTextures() {
	return textures;
}

std::vector<std::string> TextureContainer::getSigns() {
	return signs;
}

TextureContainer* TextureContainer::getInstance() {
	if (!TextureContainer::instance) {
		TextureContainer::instance = new TextureContainer;
	}
	return TextureContainer::instance;
}