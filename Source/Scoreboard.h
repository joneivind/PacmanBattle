#pragma once
#include <SFML/Graphics.hpp>
#include "Pacman.h"
using namespace sf;
using namespace std;

class Pacman;

class Scoreboard 
{
	private:
		Pacman* m_player1;
		Pacman* m_player2;
		RenderTarget* m_renderer;

	public:
		Scoreboard(RenderTarget& gameWindow, Pacman& player1, Pacman& player2);
		void displayScore(Pacman& Player1, Pacman& Player2);
		int pointsTaken = 0;
};