#ifndef DEF_COMBAT
#define DEF_COMBAT

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Textures.h"
#include "Pokemon.h"
#include "Attaque.h"
#include "Player.h"

class Combat {
public:
	Combat(sf::RenderWindow* w);
	~Combat();

	void startCombat(Player* p, Pokemon* adversaire);

	void updateCombat(Player* p, Pokemon* adversaire);
	void renderCombat(Player* p, Pokemon* adversaire);

	bool continueCombat(Player* p, Pokemon* adversaire);//verifie si le combat peut continuer ou si le player s'enfuit
	void estKO(Pokemon* p);
	void resetFuite();
	void resetPokeball();

	void startSound();
	void endSound();

private:

	sf::Event combatEven;

	Textures* terrain;
	Textures* pokeball;
	sf::RenderWindow* window;
	sf::RectangleShape textArea;
	sf::Text actionText;
	sf::RectangleShape nameAreaE, nameAreaP;
	sf::RectangleShape BarVieE, BarVieEg, BarVieP, BarViePg, BarXpG, BarXpB;
	sf::Text nameE, nameP, lvlE, lvlP, vieP, pvtxtE, pvtxtP, attaqueName;
	sf::Font font;
	sf::RectangleShape commandes[6];

	Pokemon* currPokeP;

	sf::SoundBuffer buffer;
	sf::Sound sound;
	void initSound();
	

	bool fuite; // initialisé a false. Si true, le combat est fini

	//fonctions init
	void initTerrain();
	void initPokeball();
	void initNameAreas();
	void initBars();
	void initTexts();
	void initFont();
	void styleSet(sf::Text* t);
	void initCommandes();

	void pollEvents(Pokemon* adversaire, Player* p);

	void boucleDeCombat(int indice, Pokemon* adversaire);

	void soinEquipePokemon(Player* p);

};

#endif