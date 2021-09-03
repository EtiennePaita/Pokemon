#include "Wall.h"

Wall::Wall() : Object(Elements::Wall_elem) {

}

Wall::~Wall() {

}

bool Wall::estTraversant() {
	return false;
}