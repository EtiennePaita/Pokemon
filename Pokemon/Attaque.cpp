#include "Attaque.h"

Attaque::Attaque(std::string n, int d) : name(n), degats(d) {

}

Attaque::~Attaque() {

}

int Attaque::getDegats() {
	return this->degats;
}

std::string Attaque::getName() {
	return this->name;
}