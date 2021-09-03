#ifndef DEF_POKEMON
#define DEF_POKEMON

#include <string>
#include "Textures.h"
#include "Attaque.h"

class Pokemon {
public:
	Pokemon(std::string n, int vie, float exp, int lvl, float p, float pSupp, int depX, int depY, int pasX, int pasY);
	Pokemon(std::string n, int vie, float exp, int lvl, float p, float pSupp, Textures* t);
	~Pokemon();

	void drawTexture(sf::RenderTarget& window);
	void toString();
	bool isAlive();

	//modificateurs
	void setPosition(int i, int j);
	void setPV(int x);
	void setAttaque(int x, Attaque* a);

	//accesseurs
	std::string getName();
	int getPv();
	int getPvMax();
	float getXp();
	float getXpMax();
	float getPuissance();
	int getNiveau();
	Attaque* getAttaques(int x);

	sf::Vector2f getPosition();

	void setPuissance();
	Pokemon* clone();
	void gainXp(float gain);
	void levelUp();

private:
	//attributs
	std::string name;
	int pvMAX;
	float puissance; //puissance du pokemon ( a multiplier avec les degats de l'attaque lancee)
	float puissanceSupp; // puissance suplémentaire par niveau
	int pv;
	float xp;
	float xpMax;
	int niveau;
	Textures* m_texture;

	//Poketype type;
	Attaque* attaques[4];
	void initAttaques();

	//ajouter une liste d'attaques que le pokemon pourra apprendre

	void initPokemonTexture(int depX, int depY, int pasX, int pasY);

};

#endif
