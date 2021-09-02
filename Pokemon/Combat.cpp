#include "Combat.h"
#include <iostream>

Combat::Combat(sf::RenderWindow* w) : window(w) {
    this->initFont();
    this->initTerrain();
    this->initPokeball();
    this->initNameAreas();
    this->initTexts();
    this->initBars();
    this->initCommandes();
    this->currPokeP = nullptr;
    this->fuite = false;
    this->initSound();
}

Combat::~Combat() {
    delete this->terrain;
    delete this->window;
}

void Combat::initSound() {
    if (!this->buffer.loadFromFile("../Sounds/107-battle-_vs-wild-pokemon_.wav"))
        std::cout << "Impossible de charger la musique" << std::endl;

    sound.setBuffer(this->buffer);
}

void Combat::initTerrain() {
    this->terrain = new Textures("../Textures/Combat.png", 2 * 258.3, 1 * 146.25, 258, 146);
    this->terrain->setScale(1.87f, 1.87f);
}

void Combat::initPokeball() {
    this->pokeball = new Textures("../Textures/pokemonSprite2.png", 38 * 16, 0, 16, 16);
    this->pokeball->setSpritePosition(15*80, 15*80);
}

void Combat::resetPokeball() {
    this->pokeball->setSpritePosition(15 * 80, 15 * 80);
}

void Combat::initNameAreas() {
    // ajout de la zone du nom de l'ennemi
    this->nameAreaE = sf::RectangleShape(sf::Vector2f(this->window->getSize().x / 3, 100.f));
    nameAreaE.setFillColor(sf::Color::White);
    nameAreaE.setOutlineThickness(5.f);//bords de la figure
    nameAreaE.setOutlineColor(sf::Color::Black);
    nameAreaE.setPosition(30, 30);

    // ajout de la zone du nom allie
    this->nameAreaP = sf::RectangleShape(sf::Vector2f(nameAreaE.getSize().x, nameAreaE.getSize().y + 20));
    nameAreaP.setFillColor(sf::Color::White);
    nameAreaP.setOutlineThickness(5.f);//bords de la figure
    nameAreaP.setOutlineColor(sf::Color::Black);
    nameAreaP.setPosition((this->window->getSize().x / 3) * 2 - 20, this->window->getSize().y / 3 + 60);  
}

void Combat::initBars() {

    this->BarVieEg = sf::RectangleShape(sf::Vector2f(175.f, 20.f));
    this->BarVieE = sf::RectangleShape(sf::Vector2f(175.f, 20.f));
    this->BarViePg = sf::RectangleShape(sf::Vector2f(175.f, 20.f));
    this->BarVieP = sf::RectangleShape(sf::Vector2f(175.f, 20.f));

    this->BarVieEg.setPosition(150, 85);
    this->BarVieEg.setFillColor(sf::Color(200,200,200));
    this->BarVieEg.setOutlineThickness(2.f);
    this->BarVieEg.setOutlineColor(sf::Color::Black);

    this->BarVieE.setPosition(150, 85);
    this->BarVieE.setFillColor(sf::Color::Green);
    this->BarVieE.setOutlineThickness(2.f);
    this->BarVieE.setOutlineColor(sf::Color::Black);

    this->styleSet(&this->pvtxtE);
    this->pvtxtE.setString("PV");
    this->pvtxtE.setCharacterSize(20);
    this->pvtxtE.setPosition(120, 85);
    
    this->styleSet(&this->pvtxtP);
    this->pvtxtP.setString("PV");
    this->pvtxtP.setCharacterSize(20);
    this->pvtxtP.setPosition(710, this->window->getSize().y / 3 + 120);
    

    this->BarViePg.setFillColor(sf::Color(200,200,200));
    this->BarViePg.setOutlineThickness(2.f);
    this->BarViePg.setOutlineColor(sf::Color::Black);
    this->BarViePg.setPosition(740, this->window->getSize().y / 3 + 120);

    this->BarVieP.setPosition(740, this->window->getSize().y / 3 + 120);
    this->BarVieP.setFillColor(sf::Color::Green);
    this->BarVieP.setOutlineThickness(2.f);
    this->BarVieP.setOutlineColor(sf::Color::Black);

    //bar d'xp
    this->BarXpG = sf::RectangleShape(sf::Vector2f(this->nameAreaP.getSize().x - 50, 6.f));
    this->BarXpG.setFillColor(sf::Color(200, 200, 200));
    this->BarXpG.setPosition(this->nameAreaP.getPosition().x + 50, this->nameAreaP.getPosition().y + this->nameAreaP.getSize().y + 5);
    this->BarXpG.setOutlineThickness(1.f);
    this->BarXpG.setOutlineColor(sf::Color::Black);

    this->BarXpB = sf::RectangleShape(sf::Vector2f(0.f, 0.f));
    this->BarXpB.setFillColor(sf::Color::Blue);
    this->BarXpB.setPosition(this->BarXpG.getPosition());
    this->BarXpB.setOutlineThickness(1.f);
    this->BarXpB.setOutlineColor(sf::Color::Black);

}

void Combat::initFont() {
    if (!this->font.loadFromFile("../Textures/OpenSans-Regular.ttf")) { std::cout << "font style impossible à charger" << std::endl; }

}

void Combat::initTexts() {
    this->styleSet(&this->nameE);
    this->nameE.setPosition(40, 40);
    // Pokemon adverse

    this->styleSet(&this->nameP);
    this->nameP.setPosition((this->window->getSize().x / 3) * 2, this->window->getSize().y / 3 + 70);
    // Pokemon Player

    //affichage des niveaux
    this->styleSet(&this->lvlP);
    
    this->lvlP.setPosition((this->nameAreaP.getPosition().x) + 250, this->window->getSize().y / 3 + 75);
    this->lvlP.setCharacterSize(25);

    this->styleSet(&this->lvlE);
    
    this->lvlE.setPosition(40 + 250, 45);

    this->styleSet(&this->vieP);
    this->vieP.setCharacterSize(25);

    this->styleSet(&this->actionText);
    this->actionText.setCharacterSize(20);
    
    this->styleSet(&this->attaqueName);
    this->attaqueName.setCharacterSize(30);

}

void Combat::styleSet(sf::Text* t) {
    t->setFont(font);
    t->setFillColor(sf::Color::Black);
    t->setCharacterSize(30);
    t->setStyle(sf::Text::Bold);
}

void Combat::initCommandes() {
    //affiche la zone de texte
    this->textArea = sf::RectangleShape(sf::Vector2f(this->window->getSize().x, 60));
    this->textArea.setPosition(0, 545);
    this->textArea.setFillColor(sf::Color::White);

    this->actionText.setPosition(this->textArea.getPosition().x + 10, this->textArea.getPosition().y + 10);

    //set les zones d'attaques
    for (int h = 0; h < 6; h++) {
        sf::RectangleShape rectangle(sf::Vector2f(this->window->getSize().x / 2, 120.f));
        rectangle.setOutlineThickness(2.f);
        rectangle.setFillColor(sf::Color(200, 200, 200));
        rectangle.setOutlineColor(sf::Color::Black);
        if (h < 2) {
            rectangle.setPosition((h % 2) * rectangle.getSize().x, 545 + this->textArea.getSize().y);
        }
        else if (h < 4 && h >=2){
            rectangle.setPosition((h % 2) * rectangle.getSize().x, 545 + this->textArea.getSize().y + rectangle.getSize().y);
        }
        else {
            rectangle.setPosition((h % 2) * rectangle.getSize().x, 545 + this->textArea.getSize().y + (rectangle.getSize().y * 2));

        }
        this->commandes[h] = rectangle;
    }
}

void Combat::soinEquipePokemon(Player* p) {
    p->soinEquipe();
}

void Combat::startCombat(Player* p, Pokemon* adversaire) {

    this->actionText.setString("");

    if (!p->getPokemonAlive()) return;

    this->currPokeP = p->getPokemonAlive();

    this->currPokeP->setPosition(4, 1);
    adversaire->setPosition(1, 7);

    this->nameE.setString(adversaire->getName());
    this->nameP.setString(this->currPokeP->getName());

    this->lvlE.setString("N." + std::to_string(adversaire->getNiveau()));
    this->lvlP.setString("N." + std::to_string(this->currPokeP->getNiveau()));

    this->vieP.setPosition(this->BarViePg.getPosition().x + 60, this->BarViePg.getPosition().y + 25);

}


void Combat::boucleDeCombat(int indice, Pokemon* adversaire) {
    this->actionText.setString(this->currPokeP->getName() + " utilise " + this->currPokeP->getAttaques(indice)->getName());
    adversaire->setPV(adversaire->getPv() - (this->currPokeP->getPuissance() * this->currPokeP->getAttaques(indice)->getDegats()));

}


void Combat::pollEvents(Pokemon* adversaire, Player* p) {
    
    while (this->window->pollEvent(this->combatEven))
    {
        if (this->combatEven.type == sf::Event::Closed)
            this->currPokeP->setPV(0);
        if (this->combatEven.type == sf::Event::KeyPressed) {
            
            //parcours des commandes
            int g;
            for (g = 0; g < 6; g++) {
                if (this->commandes[g].getFillColor() == sf::Color(235, 235, 235))
                    break;
            }
            if (g == 6) {
                g = 0;
                this->commandes[0].setFillColor(sf::Color(235, 235, 235));
            }
            //g definie la commande sur laquelle on se trouve

            switch (this->combatEven.key.code)
            {
            case sf::Keyboard::Z:
                if (!(g - 2 < 0)) {
                    this->commandes[g].setFillColor(sf::Color(200, 200, 200));
                    this->commandes[g-2].setFillColor(sf::Color(235, 235, 235));
                }
               
                break;
            case sf::Keyboard::Q:
                if (!((g%2) - 1 < 0)) {
                    this->commandes[g].setFillColor(sf::Color(200, 200, 200));
                    this->commandes[g - 1].setFillColor(sf::Color(235, 235, 235));
                }

                break;
            case sf::Keyboard::S:
                if (!(g + 2 > 5)) {
                    this->commandes[g].setFillColor(sf::Color(200, 200, 200));
                    this->commandes[g + 2].setFillColor(sf::Color(235, 235, 235));
                }

                break;
            case sf::Keyboard::D:
                if (!((g % 2) + 1 > 1)) {
                    this->commandes[g].setFillColor(sf::Color(200, 200, 200));
                    this->commandes[g + 1].setFillColor(sf::Color(235, 235, 235));
                }

                break;
            case sf::Keyboard::Space:
                if (g == 4) {
                    if (rand() % 5 > 0) {
                        this->actionText.setString("Vous prenez la fuite !");
                        this->fuite = true;
                    }
                    else {
                        this->actionText.setString("Vous essayez de fuir... en vain.");
                        p->setTurn(false);
                    }
                }
                else if (g == 5) {
                    p->setTurn(false);
                    if (rand() % 3 > 0) {
                        //attrape le Pokemon
                        p->setTurn(false);
                        sf::Vector2f vector = adversaire->getPosition();
                        
                        adversaire->setPosition(15, 15);

                        if (p->addToEquipe(adversaire)) {
                            this->actionText.setString("Vous avez attrappé " + adversaire->getName() + " sauvage !");
                            this->pokeball->setSpritePosition(vector.x + 50, vector.y + 50);
                        }
                        else {
                            this->actionText.setString("Votre equipe est trop pleine... "+adversaire->getName()+" sauvage est relaché.");
                        }
                        this->fuite = true;
                    }
                    else {
                        this->actionText.setString(adversaire->getName() + " sauvage est sorti de la pokeball !");
                    }

                }
                else if (this->currPokeP->getAttaques(g)) {
                    this->boucleDeCombat(g, adversaire);
                    p->setTurn(false);
                }
                

                break;
            default:
                break;
            }

        }

    }
}

void Combat::estKO(Pokemon* p) {
    p->setPosition(15, 15);
    this->actionText.setString(p->getName() + " est KO");
}


bool Combat::continueCombat(Player* p, Pokemon* adversaire) {
    if (!adversaire->isAlive()) {
        this->estKO(adversaire);
        this->currPokeP->gainXp(adversaire->getXpMax() * 0.3);
        
    }
    else if (!this->currPokeP->isAlive()) {
        this->estKO(this->currPokeP);
        std::string sname = this->currPokeP->getName();
        this->startCombat(p, adversaire); // change le currPokemon
        this->actionText.setString(sname + " est KO");
    }
    
    return ((p->getPokemonAlive() != nullptr) && (adversaire->isAlive()) && (!this->fuite));
}

void Combat::updateCombat(Player* p, Pokemon* adversaire) {

    //choix des attaques du player
    
    this->lvlE.setString("N." + std::to_string(adversaire->getNiveau()));
    this->lvlP.setString("N." + std::to_string(this->currPokeP->getNiveau()));

    if (p->Turn() && p->getPokemonAlive()) {
        this->pollEvents(adversaire, p);
    }
    else if (!p->Turn() && adversaire->isAlive()) {
        sf::Time time = sf::seconds(1.5f);
        sf::sleep(time);
        int randA = rand() % 4;
        while (!adversaire->getAttaques(randA)) {
            randA = rand() % 4;
        }
        this->currPokeP->setPV(this->currPokeP->getPv() - (adversaire->getPuissance() * adversaire->getAttaques(randA)->getDegats()));
        this->actionText.setString(adversaire->getName() + " sauvage utilise " + adversaire->getAttaques(randA)->getName());

        p->setTurn(true);
    }
    
    //update barVie des combattants
    float pourcentE = (float)adversaire->getPv() / (float)adversaire->getPvMax();
    if (pourcentE <= 0.25) this->BarVieE.setFillColor(sf::Color::Red);
    else this->BarVieE.setFillColor(sf::Color::Green);

    float pourcentP = (float)this->currPokeP->getPv() / (float)this->currPokeP->getPvMax();
    if (pourcentP <= 0.25) this->BarVieP.setFillColor(sf::Color::Red);
    else this->BarVieP.setFillColor(sf::Color::Green);

    this->BarVieE.setSize(sf::Vector2f((pourcentE) * (float)this->BarVieEg.getSize().x, (float)this->BarVieEg.getSize().y));

    this->BarVieP.setSize(sf::Vector2f((pourcentP) * (float)this->BarViePg.getSize().x, (float)this->BarViePg.getSize().y));
    
    std::string pvs = std::to_string(this->currPokeP->getPv());
    pvs += "/" + std::to_string(this->currPokeP->getPvMax());
    this->vieP.setString(pvs);

    //barXp
    float pourcentXP = (float)this->currPokeP->getXp() / (float)this->currPokeP->getXpMax();
    this->BarXpB.setSize(sf::Vector2f((pourcentXP) * (float)this->BarXpG.getSize().x, (float)this->BarXpG.getSize().y));

}


void Combat::renderCombat(Player* p, Pokemon* adversaire) {

    //affichage du terrain
    this->terrain->drawTexture(*this->window);

    //affichage des pokemons
    adversaire->drawTexture(*this->window);
    this->currPokeP->drawTexture(*this->window);

    this->pokeball->drawTexture(*this->window);

    this->window->draw(this->nameAreaE);
    this->window->draw(this->nameAreaP);

    this->window->draw(this->nameE);
    this->window->draw(this->nameP);

   
    this->window->draw(this->lvlE);
    this->window->draw(this->lvlP);

    this->window->draw(this->BarVieEg);
    this->window->draw(this->BarViePg);
    this->window->draw(this->BarVieE);
    this->window->draw(this->BarVieP);

    this->window->draw(this->pvtxtE);
    this->window->draw(this->pvtxtP);

    this->window->draw(this->vieP);

    this->window->draw(this->BarXpG);
    this->window->draw(this->BarXpB);

    this->window->draw(this->textArea);
    this->window->draw(this->actionText);
    //draw commandeZone
    for (int c = 0; c < 6; c++) {
        this->window->draw(this->commandes[c]);
    }

    //draw attacks names
    for (int h = 0; h < 6; h++) {
        if (h < 4) {
            if (this->currPokeP->getAttaques(h)) {
                this->attaqueName.setString(this->currPokeP->getAttaques(h)->getName());
                this->attaqueName.setPosition(this->commandes[h].getPosition().x + 10, this->commandes[h].getPosition().y + 10);
            }
        }
        else if (h == 4) {
            this->attaqueName.setString("Fuite");
            this->attaqueName.setPosition(this->commandes[h].getPosition().x + 10, this->commandes[h].getPosition().y + 10);
        }
        else if (h == 5) {
            this->attaqueName.setString("Attraper");
            this->attaqueName.setPosition(this->commandes[h].getPosition().x + 10, this->commandes[h].getPosition().y + 10);
        }
        this->window->draw(this->attaqueName);
    }
}

void Combat::resetFuite() {
    this->fuite = false;
}

void Combat::startSound() {
    this->sound.play();
    this->sound.setLoop(true);
}

void Combat::endSound() {
    this->sound.stop();
}