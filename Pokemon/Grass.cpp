#include "Grass.h"

Grass::Grass() : Object(Elements::Grass_elem) {

}

Grass::~Grass() {

}

bool Grass::estTraversant() {
	return true;
}