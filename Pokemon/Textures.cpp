#include "Textures.h"
#include <iostream>

Textures::Textures(std::string file) {
	this->initTexture(file);
	this->initSprite();
}

Textures::Textures(std::string file, int depX, int depY, int pasX, int pasY) : Textures(file) {
	this->sprite.setTextureRect(sf::IntRect(depX, depY, pasX, pasY));
	if (file == "../Textures/dresseur.png") {
		this->sprite.scale(1.25f, 1.25f);
	}
	else if (file == "../Textures/pokemonSprite2.png") {
		this->sprite.scale(5.f, 5.f);
	}
	else {
		this->sprite.scale(2.f, 2.f);
	}
	
}

Textures::Textures(std::string file, sf::IntRect r) : Textures(file) {
	this->sprite.setTextureRect(r);
	if (file == "../Textures/dresseur.png") {
		this->sprite.scale(1.25f, 1.25f);
	}
	else if (file == "../Textures/pokemonSprite2.png") {
		this->sprite.scale(5.f, 5.f);
	}
	else {
		this->sprite.scale(2.f, 2.f);
	}
}


Textures::~Textures() {
	
}

void Textures::initTexture(std::string file) {
	if (!this->texture.loadFromFile(file)) {
		std::cout << "ERROR::Textures::initTexture(std::string file) : Texture introuvalbe" << std::endl;
	}
}

void Textures::initSprite() {
	std::cout << "Textures::initSprite()" << std::endl;
	this->sprite.setTexture(this->texture);
}

void Textures::drawTexture(sf::RenderTarget& window) {
	window.draw(this->sprite);
}

void Textures::setSpritePosition(int x, int y) {
	this->sprite.setPosition(x, y);
}

sf::Vector2f Textures::getSpritePosition() {
	return this->sprite.getPosition();
}

void Textures::setScale(float x, float y) {
	this->sprite.scale(x,y);
}

sf::IntRect Textures::getBounds() {
	return this->sprite.getTextureRect();
}