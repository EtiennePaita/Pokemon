#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>

int main() {
	srand(time(NULL));

	Game m_game;
	m_game.startSound();

	while (m_game.isOpen()) {
		m_game.update();
		m_game.renderGame();
	}
	
	m_game.endSound();

	return 0;
}