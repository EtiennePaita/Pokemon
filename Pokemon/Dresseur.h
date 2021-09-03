#ifndef DEF_DRESSEUR
#define DEF_DRESSEUR

#include "Object.h"
#include "Pokemon.h"

class Dresseur : public Object {
public:
	Dresseur(int x, int y);
	~Dresseur();
	bool estTraversant();
	int getOrientationX();
	int getOrientationY();
	void initEquipe();
	bool addToEquipe(Pokemon* p);
	
	Pokemon* getPokemonAlive();
	void soinEquipe();
	

private:
	int orientationX;
	int orientationY;
	Pokemon* equipe[6];
};

#endif
