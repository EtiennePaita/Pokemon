#include "Object.h"

Object::Object(Elements e) : type(e) {

}

Object::~Object() {

}

Elements Object::getType() const{
	return type;
}