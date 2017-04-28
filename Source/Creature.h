#pragma once
#include <SFML\Graphics.hpp>
#include "animation.h"
#include "Creature.h"
#include <iostream>
using namespace sf;
using namespace std;

class Creature // Pacman and Ghost
{
	public:
		RectangleShape creature;
		Texture texture;
		Animation animation;
		const int groundHeight = 696; // Set ground height
		const float gravitySpeed = 800; // Set gravity force
		Vector2f position;
		Vector2f originalPosition;
		float speed; // Creature speed
		float timeInAir; // Timer
		bool isJumping = false; // Jumping?

	public:
		RectangleShape getSprite();
		FloatRect getGlobalBounds();
		void setPosition(Vector2f newPosition);
		void updatePosition(); // Set new position
};