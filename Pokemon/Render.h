#ifndef DEF_RENDER
#define DEF_RENDER

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <vector>

#include "Object.h"
#include "Textures.h"
#include "Player.h"


class Render {
public:
	Render(sf::RenderWindow* window);
	~Render();
	void renderMap(std::vector<std::vector<Object*>> centeredMap, Player* const player); // affiche le tableau 2D placé en parametre ainsi que le joueur

private:
	sf::RenderWindow* window; // pointeur sur la fenetre d'affichage de Game
	sf::VideoMode videoMode; // taille de la fenetre

	std::vector<Textures*> textureMap; // contient toutes les textures des maps
	int CaseSize; // taille d'une case
	int nbCase; //nombres de case sur une ligne


	//methodes
	void initTextureMap();// initialise toute les textures des maps à partir d'un fichier dans lequel se trouve les chemins vers des images
	void initVariables();


};

#endif
