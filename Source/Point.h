#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "animation.h"
#include "Creature.h"
#include "Pacman.h"
#include "Menu.h"
#include "Scoreboard.h"
#include <iostream>
using namespace sf;
using namespace std;

class Pacman;
class Menu;
class Scoreboard;

class Point
{
	private:
		RectangleShape point;
		Texture texture;
		Sound coin;
		SoundBuffer bufferCoin;
		bool isBig = false;

	public:
		Point();
		Point(Vector2f newPosition, bool isLarge);
		void checkCollision(Pacman& playerOne, Pacman& playerTwo, Scoreboard& scoreboard, float dt);
		void reset();
		RectangleShape getSprite();
		FloatRect getGlobalBounds();
		bool isEaten = false;
		bool soundOn = true;
};