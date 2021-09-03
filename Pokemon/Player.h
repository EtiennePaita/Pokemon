#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "Dresseur.h"

class Player : public Dresseur {
public:
	Player(int cX, int cY, int orX, int orY); // constructeur en private pour ne creer qu'un seul Player
	~Player();
	int getX();
	int getY();
	void setCoord(int x, int y);
	bool Turn();
	void setTurn(bool t);

private:
	//coordonnées renvoyant a une case du tableau d'elements de la classe Map
	int coordX;
	int coordY;
	bool turn;
};

#endif
