#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "animation.h"
#include "Creature.h"
#include "Pacman.h"
using namespace sf;

void Pacman::input(float dt, Menu& newMenu)
{
	menu = &newMenu;

	if (!newMenu.showMenu)
	{
		// Controls
		if (controls == 0) // Arrow keys
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
				moveLeft(dt);

			if (Keyboard::isKeyPressed(Keyboard::Right))
				moveRight(dt);

			if (Keyboard::isKeyPressed(Keyboard::Up) && timeInAir == 0.0f) // Jumping
			{
				if(menu->soundOn)
					jumping.play(); // Play jumping sound
				isJumping = true;
			}
			if (isJumping)
				jump(dt);
		}

		else if (controls == 1) // WASD keys
		{
			if (Keyboard::isKeyPressed(Keyboard::A))
				moveLeft(dt);

			if (Keyboard::isKeyPressed(Keyboard::D))
				moveRight(dt);

			if (Keyboard::isKeyPressed(Keyboard::W) && timeInAir == 0.0f && !isJumping) // Jumping
			{
				if (menu->soundOn)
					jumping.play(); // Play jumping sound
				isJumping = true;
			}
			if (isJumping)
				jump(dt);
		}

		// Gravity is active if not jumping
		if (position.y < groundHeight && !isJumping)
			position.y += gravitySpeed * dt;

		// Check if object is moving off screen, move back in on other side
		if (position.x > 1100.0f)
			position.x = -60.0f;

		if (position.x < -60.0f)
			position.x = 1100.0f;

		if (position.y > 800.0f)
			position.y = -60.0f;

		if (position.y < 0.0f)
			position.y = 0.0f;

		updatePosition(); // Update the position after input
	}
}