#include "Pacman.h"


Pacman::Pacman(Vector2f startPosition, int controlScheme) // Constructor
{
	creature.setFillColor(Color::White); // Set fillcolor
	texture.loadFromFile("gfx/pacman_sprites_full.png"); // Load texture from file
	creature.setTexture(&texture); // Add texture

	Vector2f spriteSize(84.0f, 84.0f);
	creature.setSize(spriteSize); // Set size
	
	animation = Animation(&texture, Vector2u(6, 10), 0.1f); // Create new animation object
	creature.setTextureRect(animation.uvRect); // Add animation to pacman

	position = startPosition; // Get start position
	originalPosition = startPosition; // Store start position
	creature.setPosition(position); // Set start position

	timeInAir = 0.0f;

	speed = 400; // Set speed

	controls = controlScheme; // Set controls

	// Load and set up sound effects
	buffer1.loadFromFile("sfx/jump.ogg");
	buffer2.loadFromFile("sfx/nsmb_flagpole.wav");
	buffer3.loadFromFile("sfx/mb_die.wav");
	jumping.setBuffer(buffer1);
	lostGame.setBuffer(buffer2);
	death.setBuffer(buffer3);
}

void Pacman::moveLeft(float dt) // Move left
{
	position.x -= speed * dt;
	creature.move(Vector2f(-speed * dt, 0.0f));
	animation.Update(0, Vector2u(3, 5), dt);
	creature.setTextureRect(animation.uvRect);
}

void Pacman::moveRight(float dt) // Move right
{
	position.x += speed * dt;
	creature.move(Vector2f(speed * dt, 0.0f));
	animation.Update(0, Vector2u(0, 2), dt);
	creature.setTextureRect(animation.uvRect);
}

void Pacman::moveStop() // Stop moving
{
	creature.move(Vector2f(0, 0));
}

void Pacman::jump(float dt) // Jump - Move up when press jump, pull down from gravity
{
	timeInAir += dt; // Delta time

	if (timeInAir < 0.15f)
	{
		position.y -= gravitySpeed*1.5 * dt;
		creature.setTextureRect(animation.uvRect);
	}
	else if (timeInAir >= 0.15f && timeInAir < 0.25f)
	{
		position.y -= gravitySpeed / 2 * dt;
		creature.setTextureRect(animation.uvRect);
	}
	else if (timeInAir >= 0.25f && timeInAir < 0.6f)
	{
		position.y += gravitySpeed * dt;
		creature.setTextureRect(animation.uvRect);
	}
	if (timeInAir > 0.6)
	{
		isJumping = false;
		timeInAir = 0.0f;
	}
}


void Pacman::reset() // Reset pacman
{
	setPosition(originalPosition);
	score = 0;
	hearts = 1;
	hasLostGame = false;
}


void Pacman::CheckCollision(Creature& enemy)
{
	// Safe zones for collisions behind the tubes

	// Top section
	if (creature.getGlobalBounds().intersects(enemy.getGlobalBounds()) && enemy.position.y <= 60 * 3 && (enemy.position.x > 120.0f && enemy.position.x < (960.0f - 84.0f)))
	{
		hasCollided = true;
	}
	// Middle section
	else if (creature.getGlobalBounds().intersects(enemy.getGlobalBounds()) && (enemy.position.y > 60 * 3 && enemy.position.y <= 60 * 11))
	{
		hasCollided = true;
	}
	// Bottom section
	else if (creature.getGlobalBounds().intersects(enemy.getGlobalBounds()) && enemy.position.y > 60 * 11 && (enemy.position.x > 120.0f && enemy.position.x < (960.0f - 84.0f)))
	{
		hasCollided = true;
	}
	// Else no collision if in safe zone
	else
		hasCollided = false;

	if (hasCollided == true) // If collided with ghost
	{
		if(!hasLostGame && menu->soundOn)
			death.play(); // Play death sound
		
		setPosition(originalPosition); // Reset to start position

		if(hearts > 0)
			hearts--; // Lost heart

		if (hearts <= 0 && !hasLostGame)
			hasLostGame = true;
	}
}

void Pacman::CheckCollisionWithPlayer(Pacman& otherPlayer) // TEST FUNCTION ONLY - NOT USED
{
	if (creature.getGlobalBounds().intersects(otherPlayer.getGlobalBounds()))
	{
		hasCollidedwithPlayer = true;

		if (creature.getPosition().x >= otherPlayer.position.x + 82.0f)
		{
			moveStop();
		}
		else
		{
			moveStop();
		}
	}
	else
		hasCollidedwithPlayer = false;
}