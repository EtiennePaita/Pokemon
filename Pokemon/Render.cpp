#include "Render.h"
#include <fstream>
#include <iostream>

Render::Render(sf::RenderWindow* window) {
	this->initVariables();
	this->window = window;
	this->initTextureMap();
}

Render::~Render() {

}

void Render::initVariables() {
	this->window = nullptr;
	this->CaseSize = 80;
	this->nbCase = 12;
}


void Render::initTextureMap() {
	std::string file = "../Textures/pokemonSprite2.png";
	//GrassTexture
	Textures* newT = new Textures(file,0,0,16,16);
	this->textureMap.push_back(newT);
	//TallGrassTexture
	Textures* newTal = new Textures(file, 16*3, 16*2, 16, 16);
	this->textureMap.push_back(newTal);
	//WallTexture
	Textures* newW = new Textures(file, 0, 16*28,16,16);
	this->textureMap.push_back(newW);
	//DresseurTexture
	Textures* newD = new Textures("../Textures/dresseur.png",0,0,64,64);
	this->textureMap.push_back(newD);

}

void Render::renderMap(std::vector<std::vector<Object*>> centeredMap, Player* const player) {
	Textures* grassT = this->textureMap[(int)Elements::Grass_elem];
	for (int i = 0; i < centeredMap.size(); i++) {
		for (int j = 0; j < centeredMap[i].size(); j++) {
			Elements m_type = centeredMap[i][j]->getType();
			Textures* m_texture = this->textureMap[(int)m_type];
			 
			grassT->setSpritePosition(this->CaseSize * j, this->CaseSize * i);
			grassT->drawTexture(*this->window);
			
			if (m_type != Elements::Grass_elem && m_type != Elements::Dresseur_elem) {
				m_texture->setSpritePosition(this->CaseSize * j, this->CaseSize * i);
				m_texture->drawTexture(*this->window);
			}
		}
	}
	Textures* dresseur_texture = this->textureMap[(int)player->getType()];

	dresseur_texture->setSpritePosition(this->CaseSize * (this->nbCase/2), this->CaseSize * (this->nbCase/2));
	dresseur_texture->drawTexture(*this->window);
	
}
