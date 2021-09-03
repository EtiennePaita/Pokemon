#include "TallGrass.h"

TallGrass::TallGrass() : Object(Elements::TallGrass_elem) {
	this->utilisee = false;
}

TallGrass::~TallGrass() {

}

bool TallGrass::estTraversant() {
	return true;
}

void TallGrass::estDessus() {
	this->utilisee = true;
}

void TallGrass::pasDessus() {
	this->utilisee = false;
}

bool TallGrass::estUtilisee() {
	return this->utilisee;
}