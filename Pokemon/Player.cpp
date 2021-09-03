#include "Player.h"

Player::Player(int cX, int cY, int orX, int orY) : Dresseur(orX, orY), coordX(cX), coordY(cY), turn(true) {

}

Player::~Player() {

}

int Player::getX() {
	return coordX;
}

int Player::getY() {
	return coordY;
}

void Player::setCoord(int x, int y) {
	this->coordX = x;
	this->coordY = y;
}

bool Player::Turn() {
	return turn;
}

void Player::setTurn(bool t) {
	this->turn = t;
}