#ifndef DEF_ATTAQUE
#define DEF_ATTAQUE
#include <string>

class Attaque {
public:
	Attaque(std::string n, int d);
	~Attaque();
	int getDegats();
	std::string getName();

private:
	std::string name;
	int degats;

};


#endif
