#include "Dresseur.h"
#include <iostream>

Dresseur::Dresseur(int x, int y) : Object(Elements::Dresseur_elem), orientationX(x), orientationY(y) {
	this->initEquipe();
}

Dresseur::~Dresseur() {
	
	for (int i = 0; i < 6; i++) {
		delete this->equipe[i];
	}
}

bool Dresseur::estTraversant() {
	return false;
}

int Dresseur::getOrientationX() {
	return orientationX;
}

int Dresseur::getOrientationY() {
	return orientationY;
}

void Dresseur::initEquipe() {
	for (int i = 0; i < 6; i++) {
		this->equipe[i] = nullptr;
	}
}

bool Dresseur::addToEquipe(Pokemon* p) {
	int i = 0;
	while (i < 6 && this->equipe[i] != nullptr) {
		i++;
	}

	if (i == 5) {
		std::cout << "equipe complete" << std::endl;
		return false;
	}

	this->equipe[i] = p->clone();
	return true;
}

Pokemon* Dresseur::getPokemonAlive() {
	int i = 0;
	while (i < 6 && this->equipe[i]) {
		if (!this->equipe[i]->isAlive()) {
			i++;
		}
		else {
			break;
		}
	}
	if (i == 6) {
		
		return nullptr;
	}
	return this->equipe[i];
}

void Dresseur::soinEquipe() {
	for (int i = 0; i < 6; i++) {
		if (this->equipe[i]) {
			this->equipe[i]->setPV(this->equipe[i]->getPvMax());
		}
	}
}