#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "animation.h"
#include "Creature.h"
#include "Pacman.h"
#include "Menu.h"
using namespace sf;

class Menu;

class Ghost : public Creature
{
	private:
		int ghostColor;
		Sound outOfPipe;
		SoundBuffer buffer1;
		Menu* menu;
		bool direction;

	public:
		Ghost(Vector2f startPosition);
		void setDirection(bool newDirection);
		void move(Creature playerOne, Creature playerTwo, float dt, Menu& newMenu);
		void CheckCollisionWithGhost(Ghost& otherGhost);
		void reset();
};