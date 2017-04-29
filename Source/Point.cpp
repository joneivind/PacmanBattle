#include "Point.h"


Point::Point()
{
}

Point::Point(Vector2f newPosition, bool isLarge) // Constructor
{
	point.setFillColor(Color::White); // Set fillcolor
	texture.loadFromFile("gfx/pacman_sprites_full.png"); // Load texture from file
	texture.setSmooth(1); // Smooth texture
	point.setTexture(&texture); // Add texture
	point.setSize(Vector2f(60.0f, 60.0f)); // Set size

	isBig = isLarge; // Store point size

	// Set size of point
	if (isLarge)
		point.setTextureRect(IntRect(12, 604, 60, 60));
	else 
		point.setTextureRect(IntRect(96, 604, 60, 60));

	// Set position of point
	point.setPosition(Vector2f(newPosition.x*60.0f - 60.0f, newPosition.y*60.0f));

	// Adding sound effects
	bufferCoin.loadFromFile("sfx/smb_coin.wav");
	coin.setBuffer(bufferCoin);
}

RectangleShape Point::getSprite() // Get rectangleShape
{
	return point;
}

FloatRect Point::getGlobalBounds() // Get borders
{
	return point.getGlobalBounds(); 
}

void Point::checkCollision(Pacman & playerOne, Pacman & playerTwo, Scoreboard & scoreboard, float dt) // Check collision with players
{
	if (playerOne.getGlobalBounds().intersects(point.getGlobalBounds()) && !isEaten)
	{
		point.setTextureRect(IntRect(340, 600, 84, 84)); // Change texture
		isEaten = true; // Hide point
		coin.setBuffer(bufferCoin);
		if(soundOn)
			coin.play(); // Play sound

		if(!isBig)
			playerOne.score += 500; // Add score to player
		else
			playerOne.score += 2000; // Add score to player

		scoreboard.pointsTaken++; // Add point to total points taken in scoreboard
	}

	if (playerTwo.getGlobalBounds().intersects(point.getGlobalBounds()) && !isEaten)
	{
		point.setTextureRect(IntRect(340, 600, 84, 84)); // Change texture
		isEaten = true; // Hide point
		coin.setBuffer(bufferCoin);
		if(soundOn)
			coin.play(); // Play sound

		if (!isBig)
			playerTwo.score += 500; // Add score to player
		else
			playerTwo.score += 2000; // Add score to player

		scoreboard.pointsTaken++; // Add point to total points taken in scoreboard
	}
}

void Point::reset()
{
	isEaten = false;
	if (isBig)
		point.setTextureRect(IntRect(12, 604, 60, 60));
	else
		point.setTextureRect(IntRect(96, 604, 60, 60));
}
