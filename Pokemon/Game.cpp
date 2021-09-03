#include "Game.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "Wall.h"
#include "TallGrass.h"


//private methods
void Game::initWindow() {
    this->videoMode.height = this->space * this->nbCase; //46
    this->videoMode.width = this->space * this->nbCase; //51
    this->window = new sf::RenderWindow(this->videoMode, "Pokemon");
}

void Game::initVariables() {
    this->window = nullptr;
    this->player = nullptr;
    this->space = 80;
    this->nbCase = 12;
    this->currentMapID = 0;
}

void Game::initPlayer() {
    //parcours de la map courante à la recherche du Player
    std::vector<std::vector<Object*>> curMap = this->tabMap[this->currentMapID]->getMap();

    for (int i = 0; i < curMap.size(); i++) {
        for (int j = 0; j < curMap[i].size(); j++) {
            if (curMap[i][j]->getType() == Elements::Dresseur_elem) {
                this->player = dynamic_cast<Player*>(curMap[i][j]);
                break;
            }
        }
        if (this->player) break;
    }

}

void Game::initTabMap() {
    std::ifstream monflux("../Maps/AllMaps.txt");

    if (monflux) {
        std::string ligne;

        while (std::getline(monflux, ligne)) {
            Map* newMap = new Map(ligne);
            this->tabMap.push_back(newMap);
        }
    }
}

void Game::initRender() {
    this->render = new Render(this->window);
}

void Game::initCenteredMap() {
    int xPlayer = this->player->getX();
    int yPlayer = this->player->getY();
    
    //pour que le map soit à l'endroit, il faut inverser les coordonnees x et y du player
    int i = yPlayer - (this->nbCase / 2);
    while ((i < yPlayer + (this->nbCase / 2))) {
        std::vector<Object*> tmp;
        
        int j = xPlayer - (this->nbCase / 2);
        while ((j < xPlayer + (this->nbCase / 2)) ) {
            // Creation de mur hors map si necessaire
            if (i < 0 || j < 0) {
                tmp.push_back(new Wall());
            }
            else if ((i >= this->tabMap[this->currentMapID]->getMap().size()) || (j >= this->tabMap[this->currentMapID]->getMap()[i].size())) {
                tmp.push_back(new Wall());
            }
            else {
                tmp.push_back(this->tabMap[this->currentMapID]->getMap()[i][j]);
            }
            
            j++;
        }
        this->centeredMap.push_back(tmp);
        i++;
    }

}

void Game::initPokemonListe() {
    std::ifstream monflux("../Textures/PokemonListe.txt");

    if (monflux) {
        std::string ligne;

        std::string name;
        float vie;
        float exp;
        int lvl;
        float puissance;
        float puissanceSupp;
        int depX;
        int depY;
        int pasX;
        int pasY;
        
        while (monflux) {
            monflux >> name;
            monflux >> vie;
            monflux >> exp;
            monflux >> lvl;
            monflux >> puissance;
            monflux >> puissanceSupp;
            monflux >> depX;
            monflux >> depY;
            monflux >> pasX;
            monflux >> pasY;

            this->PokemonListe.push_back(new Pokemon(name, vie, exp, lvl, puissance, puissanceSupp, depX, depY, pasX, pasY));
        }
    }
}

void Game::initCombat() {
    this->combat = new Combat(this->window);
}

void Game::initDialogue() {
    this->afficheDialogue = false;

    this->dialogueArea = sf::RectangleShape(sf::Vector2f(this->window->getSize().x, 60));
    this->dialogueArea.setPosition(0, this->window->getSize().y - 60);
    this->dialogueArea.setFillColor(sf::Color::White);
    this->dialogueArea.setOutlineColor(sf::Color::Black);
    this->dialogueArea.setOutlineThickness(3.f);

    
    if (!this->font.loadFromFile("../Textures/OpenSans-Regular.ttf")) { std::cout << "font style impossible à charger" << std::endl; }

    this->dialogue.setFont(this->font);
    this->dialogue.setFillColor(sf::Color::Black);
    this->dialogue.setCharacterSize(30);
    this->dialogue.setStyle(sf::Text::Bold);
    this->dialogue.setString("");
    this->dialogue.setPosition(this->dialogueArea.getPosition().x + 10, this->dialogueArea.getPosition().y + 10);
}

void Game::initSound() {
    if (!this->buffer.loadFromFile("../Sounds/120-pokemon-gym.wav"))
        std::cout << "Impossible de charger la musique" << std::endl;

    this->sound.setBuffer(this->buffer);
}

//Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initRender();
    this->initTabMap();
    this->initPlayer();
    this->initCenteredMap();
    this->initPokemonListe();
    this->initDialogue();
    this->initSound();

    this->player->addToEquipe(this->PokemonListe[0]);
    
    this->initCombat();
}

//Destructor
Game::~Game() {
    delete this->window;
    delete this->player;
    delete this->render;
}

//Public methods
const bool Game::isOpen() {
    return this->window->isOpen();
}

bool Game::mouvementPossible(int x, int y) {
    return (this->tabMap[this->currentMapID]->getMap()[y][x]->estTraversant());
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->even))
    {
        if (this->even.type == sf::Event::Closed)
            this->window->close();
        if (this->even.type == sf::Event::KeyPressed) {
            int x = this->player->getX();
            int y = this->player->getY();
            switch (this->even.key.code)
            {
            case sf::Keyboard::Z:
                if ((y - 1) >= 0 && mouvementPossible(x,y - 1)) {
                    if (this->tabMap[this->currentMapID]->getMap()[y][x]->getType() == Elements::TallGrass_elem) {
                        dynamic_cast<TallGrass*>(this->tabMap[this->currentMapID]->getMap()[y][x])->pasDessus();
                    }
                    this->player->setCoord(x, y - 1);
                    std::cout << "je me deplace vers le haut" << std::endl;
                }
                break;
            case sf::Keyboard::Q:
                if ((x - 1) >= 0 && mouvementPossible(x - 1, y)) {
                    if (this->tabMap[this->currentMapID]->getMap()[y][x]->getType() == Elements::TallGrass_elem) {
                        dynamic_cast<TallGrass*>(this->tabMap[this->currentMapID]->getMap()[y][x])->pasDessus();
                    }
                    this->player->setCoord(x - 1, y);
                    std::cout << "je me deplace vers la gauche" << std::endl;
                }
                break;
            case sf::Keyboard::S:
                if ((y<this->tabMap[this->currentMapID]->getMap().size()-1) && mouvementPossible(x, y + 1)) {
                    if (this->tabMap[this->currentMapID]->getMap()[y][x]->getType() == Elements::TallGrass_elem) {
                        dynamic_cast<TallGrass*>(this->tabMap[this->currentMapID]->getMap()[y][x])->pasDessus();
                    }
                    this->player->setCoord(x, y + 1);
                    std::cout << "je me deplace vers le bas" << std::endl;
                }
                break;
            case sf::Keyboard::D:
                if (mouvementPossible(x + 1, y)) {
                    if (this->tabMap[this->currentMapID]->getMap()[y][x]->getType() == Elements::TallGrass_elem) {
                        dynamic_cast<TallGrass*>(this->tabMap[this->currentMapID]->getMap()[y][x])->pasDessus();
                    }
                    this->player->setCoord(x + 1, y);
                    std::cout << "je me deplace vers la droite" << std::endl;
                }
                break;
            case sf::Keyboard::H:
                this->player->soinEquipe();
                this->dialogue.setString("Votre equipe est soignée !");
                this->afficheDialogue = true;
            default:
                break;
            }

        }

    }
}

void Game::updateCenteredMap() {
    //Pareil que initCenteredMap() sauf qu'on creer et remplace centeredMap
    std::vector<std::vector<Object*>> c;
    int xPlayer = this->player->getX();
    int yPlayer = this->player->getY();

    int i = yPlayer - (this->nbCase / 2);
    while ((i < yPlayer + (this->nbCase / 2))) {
        std::vector<Object*> tmp;

        int j = xPlayer - (this->nbCase / 2);
        while ((j < xPlayer + (this->nbCase / 2))) {
            if (i < 0 || j < 0) {
                tmp.push_back(new Wall());
            }
            else if ((i >= this->tabMap[this->currentMapID]->getMap().size()) || (j >= this->tabMap[this->currentMapID]->getMap()[i].size())) {
                tmp.push_back(new Wall());
            }
            else {
                tmp.push_back(this->tabMap[this->currentMapID]->getMap()[i][j]);
            }

            j++;
        }
        c.push_back(tmp);
        i++;
    }
    this->centeredMap = c;
}

void Game::estTallGrass() {
    int x = this->player->getX();
    int y = this->player->getY();
    
    if ((this->tabMap[this->currentMapID]->getMap()[y][x]->getType() == Elements::TallGrass_elem)) {
        TallGrass* tlg = dynamic_cast<TallGrass*>(this->tabMap[this->currentMapID]->getMap()[y][x]);
        if (!(tlg->estUtilisee())) {
            int proba = rand() % 100;
            std::cout << proba << std::endl;
            if ((proba < 18)) {
                
                this->combatPokemon();

                tlg->estDessus(); // IMPORTANT : MET A LA VALEUR TRUE LA VARIABLE utlisee
            }
            else {
                tlg->estDessus(); // pour ne pas réessayer la proba d'avoir un pokemon
            }

        }
        

    }
}

void Game::combatPokemon() {
    sf::Time time = sf::seconds(0.5f);

    this->sound.pause();
    this->combat->startSound();
    this->window->clear();
    this->window->display();
    sf::sleep(time);

    int r = rand() % this->PokemonListe.size();

    this->combat->startCombat(this->player,this->PokemonListe[r]);

    time = sf::seconds(2);
    while (this->combat->continueCombat(this->player, this->PokemonListe[r])) {
        this->window->clear();
        this->combat->updateCombat(this->player, this->PokemonListe[r]);
        this->combat->renderCombat(this->player, this->PokemonListe[r]);
        this->window->display();
    }
    this->combat->resetFuite();
    this->player->setTurn(true); // remet le tour de jeu au joueur

    this->window->clear();
    this->combat->updateCombat(this->player, this->PokemonListe[r]);
    this->combat->renderCombat(this->player, this->PokemonListe[r]);
    this->window->display();

    sf::sleep(time);

    //Soigne les pokemons sauvages à la fin de chaque combat
    this->PokemonListe[r]->setPV(this->PokemonListe[r]->getPvMax());

    this->combat->resetPokeball();

    time = sf::seconds(0.5f);
    this->combat->endSound();
    this->window->clear();
    this->window->display();
    sf::sleep(time);
    this->sound.play();
  
}

void Game::update() {
    this->pollEvents();
    this->updateCenteredMap();
    this->estTallGrass();
}

void Game::renderGame() {
    this->window->clear();
    this->render->renderMap(this->centeredMap, this->player);
    if (afficheDialogue) {
        this->window->draw(this->dialogueArea);
        this->window->draw(this->dialogue);
    }

    this->window->display();

    if (afficheDialogue) {
        sf::Time time = sf::seconds(3);
        sf::sleep(time);
        this->afficheDialogue = false;
    }
}

void Game::renderTest() {
    this->window->clear();
    sf::CircleShape shape(50);
    this->window->draw(shape);
    this->window->display();
}

void Game::startSound() {
    this->sound.play();
    this->sound.setLoop(true);
}

void Game::endSound() {
    this->sound.stop();
}