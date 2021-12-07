#include "TextureContainer.h"
#include <iostream>

TextureContainer* TextureContainer::instance = nullptr;

TextureContainer::TextureContainer() {
	std::ifstream file("TextureAlphabet.txt");
	std::string sign;
	std::string filename;
	while (file >> sign >> filename) {
		if (sign != "_") {
			sf::Image* image = new sf::Image;
			sf::Texture *texture = new sf::Texture;

			image->loadFromFile(filename);
			texture->loadFromFile(filename);
			
			alphabet_images.emplace(sign, image);
			std::map<uint8_t, sf::Texture*> map;
			map[1] = texture;
			alphabet_textures1.emplace(sign, map);
			for (int i = 2; i <= 4; i++) {
				std::cout << i << std::endl;
				alphabet_textures1[sign].emplace(i, rotateTexture(alphabet_textures1[sign][i-1]));
			}

			alphabet_textures.emplace(sign, texture);
			alphabet_links.emplace(sign, filename);
			signs.push_back(sign);
			textures.push_back(texture);
			links.push_back(filename);
		}
	}
	file.close();
}

sf::Texture* TextureContainer::getTexture(std::string sign, uint8_t sost) {
	return alphabet_textures1[sign][sost];
}

sf::Texture* TextureContainer::getTexture(std::string sign) {
	return alphabet_textures[sign];
}

std::string TextureContainer::getLink(std::string sign) {
	return alphabet_links[sign];
}

std::vector<sf::Texture*> TextureContainer::getTextures() {
	return textures;
}

std::vector<std::string> TextureContainer::getSigns() {
	return signs;
}

std::vector<std::string> TextureContainer::getLinks() {
	return links;
}

sf::Texture* TextureContainer::rotateTexture(sf::Texture* texture) { 
	sf::Image image = texture->copyToImage();
	const sf::Uint8* pixels = image.getPixelsPtr();

	std::vector<std::vector<sf::Color>> texture_in_pixels;
	sf::Uint8* pix = new sf::Uint8[64 * 64 * 4];

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