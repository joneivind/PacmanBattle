#include "Ghost.h"

Ghost::Ghost(Vector2f startPosition) // Ghost constructor
{
	creature.setFillColor(Color::White); // Set fillcolor
	texture.loadFromFile("gfx/pacman_sprites_full.png"); // Load texture from file
	creature.setTexture(&texture); // Add texture

	Vector2f spriteSize(84.0f, 84.0f); // Set size
	creature.setSize(spriteSize); // ... to ghost

	animation = Animation(&texture, Vector2u(6, 10), 0.1f); // Create new animation object
	creature.setTextureRect(animation.uvRect); // Add animation to ghost

	position = startPosition; // Get start position
	originalPosition = startPosition; // Store start position
	creature.setPosition(position); // Set start position

	direction = rand() % 2; // Start in random direction
	ghostColor = (rand() % 5) + 2; // Random ghost color

	speed = 150 + rand() % 100; // Random speed of ghost

	// Load and set up sound effects
	buffer1.loadFromFile("sfx/mb_sc.wav");
	outOfPipe.setBuffer(buffer1);
}

void Ghost::setDirection(bool newDirection) // Set direction of ghost, 0->right, 1->left
{
	direction = newDirection;
}

void Ghost::move(Creature playerOne, Creature playerTwo, float dt, Menu& newMenu) // Move ghost
{
	menu = &newMenu;

	if (!newMenu.showMenu) // Stop moving if menu is open
	{
		// Ghost follow player if on the same level and if under 300px in x-radius
		if
			(playerOne.position.x > position.x - 300 &&
				playerOne.position.x < position.x &&
				playerOne.position.y < position.y + 60 &&
				playerOne.position.y > position.y - 60)
			direction = 1;
		else if
			(playerOne.position.x < position.x + 300 + 82.0f &&
				playerOne.position.x > position.x + 82.0f &&
				playerOne.position.y < position.y + 60 &&
				playerOne.position.y > position.y - 60)
			direction = 0;
		if
			(playerTwo.position.x > position.x - 300 &&
				playerTwo.position.x < position.x &&
				playerTwo.position.y < position.y + 60 &&
				playerTwo.position.y > position.y - 60)
			direction = 1;
		else if
			(playerTwo.position.x < position.x + 300 + 82.0f &&
				playerTwo.position.x > position.x + 82.0f &&
				playerTwo.position.y < position.y + 60 &&
				playerTwo.position.y > position.y - 60)
			direction = 0;

		// Move ghost
		if (direction) // Move left
		{
			position.x -= speed * dt;
			creature.move(Vector2f(-speed * dt, 0.0f)); // Move
			animation.Update(ghostColor, Vector2u(2, 2), dt); // Update animation
			creature.setTextureRect(animation.uvRect);
		}
		else if (!direction) // Move right
		{
			position.x += speed * dt;
			creature.move(Vector2f(speed * dt, 0.0f)); // Move
			animation.Update(ghostColor, Vector2u(1, 1), dt); // Update animation
			creature.setTextureRect(animation.uvRect);
		}

		// Check if object is moving off screen
		if (position.x > 1100.0f)
			position.x = -84.0f;
		if (position.x < -84.0f)
			position.x = 1100.0f;
		if (position.y > 800.0f)
			position.y = -84.0f;
		if (position.y < 0.0f)
			position.y = 0.0f;

		// Reset ghost when pipe on bottom of the map is reached
		if (position.y > 60 * 11 && (position.x < 0.0f || position.x > 960.0f)) 
		{
			position = originalPosition; // Reset position
			direction = rand() % 2; // New random direction
			ghostColor = (rand() % 5) + 2; // New random color
			speed = 150 + rand() % 100; // Set new random speed
			updatePosition();
			if (menu->soundOn)
				outOfPipe.play(); // Play sound
		}

		// Gravity
		if (position.y < groundHeight)
			creature.move(Vector2f(0.0f, gravitySpeed * dt));
	}
}

void Ghost::CheckCollisionWithGhost(Ghost& otherGhost) // NOT USED
{
	if (creature.getPosition().x >= otherGhost.position.x - 84)
	{
		direction = 1;
		otherGhost.direction = 0;
	}
	else if (creature.getPosition().x <= otherGhost.position.x + 84)
	{
		direction = 0;
		otherGhost.direction = 1;
	}
}

void Ghost::reset()
{
	position = originalPosition; // Reset position
	direction = rand() % 2; // New random direction
	ghostColor = (rand() % 5) + 2; // New random color
	speed = 150 + rand() % 100; // Set new random speed
	updatePosition();
}
