#include "Pokemon.h"
#include <iostream>

Pokemon::Pokemon(std::string n, int vie, float exp, int lvl, float p, float pSupp, int depX, int depY, int pasX, int pasY) : name(n), pv(vie), xpMax(exp), niveau(lvl), pvMAX(vie), puissance(p), puissanceSupp(pSupp) {
	this->xp = 0;
	this->initPokemonTexture(depX, depY, pasX, pasY);
	this->initAttaques();
}

Pokemon::Pokemon(std::string n, int vie, float exp, int lvl, float p, float pSupp, Textures* t) : name(n), pv(vie), xpMax(exp), niveau(lvl), pvMAX(vie), puissance(p), puissanceSupp(pSupp) {
	this->xp = 0;
	this->m_texture = new Textures("../Textures/Pokemons.png",t->getBounds());
	this->m_texture->setScale(2.f, 2.f);
	this->initAttaques();
}

Pokemon::~Pokemon() {
	delete m_texture;
}

void Pokemon::initPokemonTexture(int depX, int depY, int pasX, int pasY) {
	this->m_texture = new Textures("../Textures/Pokemons.png", depY*pasY, depX*pasX, pasX, pasY);
	this->m_texture->setScale(2.f, 2.f);
}

void Pokemon::initAttaques() {
	this->attaques[0] = new Attaque("Charge", 25);
	for (int i = 1; i < 4; i++) {
		this->attaques[i] = nullptr;
	}
}

Attaque* Pokemon::getAttaques(int x) {
	if (x < 4) {
		return this->attaques[x];
	}
	else {
		std::cout << "Pokemon::getAttaques : Erreur index" << std::endl;
		return nullptr;
	}
}

void Pokemon::drawTexture(sf::RenderTarget& window) {
	this->m_texture->drawTexture(window);
}

void Pokemon::toString() {
	std::cout << this->name << std::endl;
}

void Pokemon::setPosition(int i, int j) {
	this->m_texture->setSpritePosition(80 * j, 80 * i);
}

sf::Vector2f Pokemon::getPosition() {
	return this->m_texture->getSpritePosition();
}

std::string Pokemon::getName() {
	return this->name;
}

int Pokemon::getPv() {
	return this->pv;
}

int Pokemon::getPvMax() {
	return this->pvMAX;
}

int Pokemon::getNiveau() {
	return this->niveau;
}

float Pokemon::getXp() {
	return this->xp;
}

float Pokemon::getXpMax() {
	return this->xpMax;
}

float Pokemon::getPuissance() {
	return this->puissance;
}

void Pokemon::setPuissance() {
	this->puissance += this->puissanceSupp;
}

bool Pokemon::isAlive() {
	return (this->pv > 0);
}

void Pokemon::setPV(int x) {
	if (x < 0) this->pv = 0;
	else this->pv = x;
}

void Pokemon::setAttaque(int x, Attaque* a) {
	if (a && x < 4) this->attaques[x] = a;
}

Pokemon* Pokemon::clone() {
	Pokemon* newPok = new Pokemon(this->name, this->pvMAX, this->xpMax, this->niveau, this->puissance, this->puissanceSupp, this->m_texture);
	newPok->setPV(this->getPv());
	newPok->niveau = this->niveau;
	
	for (int i = 0; i < 4; i++) {
		newPok->attaques[i] = this->attaques[i];
	}

	return newPok;
}

void Pokemon::gainXp(float gain) {
	this->xp += gain;
	this->levelUp();
}

void Pokemon::levelUp() {
	while (this->xp >= this->xpMax) {
		this->niveau++;
		std::cout << "Niveau supérieur ! N." << this->niveau << std::endl;
		this->puissance += this->puissanceSupp;
		this->pv += 5;
		this->pvMAX += 5;
		this->xp -= this->xpMax;
		this->xpMax = this->xpMax * 2;

	}
}