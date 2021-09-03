#ifndef DEF_GAME
#define DEF_GAME

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "Dresseur.h"
#include "Player.h"
#include "Map.h"
#include "Render.h"
#include "Pokemon.h"
#include "Combat.h"


class Game {
public:
	//constructeur , destructeur
	Game();
	~Game();

	//fonctions
	void update();	//actualiser la partie
	void renderGame();	//afficher la partie
	const bool isOpen();	//le jeu est lancé

	void renderTest();
	void startSound();
	void endSound();

private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event even; // evenements clavier
	Player* player;
	double space;	//distance d'un déplacement

	Combat* combat;
	void initCombat();

	std::vector<Map*> tabMap; // tableau contenant des pointeurs, pointants sur toutes les map du jeu
	int currentMapID; // indice de la map courrante de tabMap
	Render* render; // gere le rendu visuelle

	sf::RectangleShape dialogueArea;
	sf::Font font;
	sf::Text dialogue;
	bool afficheDialogue;
	void initDialogue();

	std::vector<std::vector<Object*>> centeredMap; //sert uniquement a etre afficher
	int nbCase;
	void updateCenteredMap();
	void initCenteredMap();

	sf::SoundBuffer buffer;
	sf::Sound sound;
	void initSound();

	std::vector<Pokemon*> PokemonListe;
	void initPokemonListe();

	void pollEvents();	//action en fonction des evenements clavier

	void initWindow();
	void initVariables();
	void initPlayer();
	void initRender();

	void initTabMap();
	bool mouvementPossible(int x, int y);

	void estTallGrass(); // verifie si le joueur se trouve sur l'element TallGrass

	void combatPokemon();
		

};

#endif
