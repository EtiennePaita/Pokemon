/*
	Fonction de création de Map.
	Il faut placer un fichier en parametre du constructeur pour creer une map
*/

#include "Map.h"
#include "Grass.h"
#include "TallGrass.h"
#include "Wall.h"
#include "Dresseur.h"
#include "Player.h"

#include <iostream>
#include <fstream>

Map::Map(std::string file) {
	this->loadMap(file);
}

Map::~Map() {
	
}

void Map::loadMap(std::string file) {
	std::ifstream monflux(file);

	if (monflux) {
		std::string ligne;
		int i = 0;
		while (std::getline(monflux, ligne)) {  // recuperation d'une ligne dans mon fichier
			std::vector<Object*> tmp;
			for (int j = 0; j < ligne.size(); j++) {
				switch (ligne[j])
				{
				case '0':
					tmp.push_back(new Grass());
					break;
				case '1':
					tmp.push_back(new TallGrass());
					break;
				case '2':
					tmp.push_back(new Wall());
					break;
				case 'P':
					tmp.push_back(new Player(j,i,0,1));
					break;
				default:
					tmp.push_back(new Grass());
					break;
				}
			}
			this->m_map.push_back(tmp);
			i++;
		}
	}
	else {
		std::cout << "ERROR::Map::loadMap";
	}
}

std::vector<std::vector<Object*>> Map::getMap(){
	return this->m_map;
}
