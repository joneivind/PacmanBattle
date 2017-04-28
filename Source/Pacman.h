#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <String>
#include "animation.h"
#include "Creature.h"
#include "Menu.h"
using namespace sf;

class Menu;

class Pacman : public Creature
{
	private:
		Sound jumping, lostGame, death;
		SoundBuffer buffer1, buffer2, buffer3;
		Menu* menu;
		int controls;
		float timeAfterCollision = 0.0f;
		bool hasCollided = false;
		bool hasCollidedwithPlayer = false;
		bool hasLostGame = false;

	public:
		Pacman(Vector2f startPosition, int controlScheme);
		void CheckCollision(Creature& enemy);
		void CheckCollisionWithPlayer(Pacman& otherPlayer);
		void input(float dt, Menu &newMenu);
		void moveLeft(float dt);
		void moveRight(float dt);
		void moveStop();
		void jump(float dt);
		void reset();
		int hearts = 1;
		int score = 0;
};