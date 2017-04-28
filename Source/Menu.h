#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Pacman.h"
#include "Ghost.h"
#include "Point.h"
#include "Scoreboard.h"
using namespace sf;
using namespace std;

class Pacman; // Dummy classes
class Ghost;
class Point;
class Scoreboard;

class Menu
{
	private:
		Font emulogic;
		Text cursor, resume, restart, music, sounds, quit, endOfRound;
		RectangleShape menuBackground, menuEnd;
		Sound open, change, cycle, end, start;
		SoundBuffer buffer1, buffer2, buffer3, buffer4, buffer5;
		Music* song;
		Pacman* player1;
		Pacman* player2;
		Ghost* ghost1;
		Ghost* ghost2;
		vector<Point>* points;
		Scoreboard* scoreboard;
		int fontSize = 20;
		float menuOffsetX = 390;
		float menuOffsetY = 200;
		float menuSizeX = 300;
		float menuSizeY = 200;
		float itemOffsetY = 40;
		float cursorPosition;
		float cursorTimer = 0;
		float cursorDelay = 0.1;
		int menuItem = 0;
		int lastItem = 4;

	public:
		Menu(Pacman& playerOne, Pacman& playerTwo, Ghost& ghostOne, Ghost& ghostTwo, vector<Point>& pointVector, Scoreboard& newScoreboard, Music& newSong);
		void displayMenu(RenderWindow& newWindow, float dt);
		void endOfGame(RenderWindow& newWindow, float dt);
		void resetGame();
		bool showMenu = false;
		bool musicOn = true;
		bool soundOn = true;
};