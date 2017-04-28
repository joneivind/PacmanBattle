#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Creature.h"
using namespace sf;
using namespace std;

class Box
{
	private:
		RectangleShape box;
		int xSize;

	public:
		Box(int sizeX, int sizeY, int posX, int posY);
		void CheckCollision(Creature& newCreature);
		FloatRect getGlobalBounds();
		Vector2f getPosition();
		RectangleShape getSprite();
};