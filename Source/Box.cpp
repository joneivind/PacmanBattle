#include "Box.h"

Box::Box(int sizeX, int sizeY, int posX, int posY) // Constructor
{
	box.setSize(Vector2f(60.0f * sizeX, 60.0f * sizeY)); // Size of box
	box.setPosition(Vector2f(60.0f * posX, 60.0f * posY)); // Box position
	box.setFillColor(Color::White); // Color
	xSize = sizeX;
}

FloatRect Box::getGlobalBounds() { // Get borders
	return box.getGlobalBounds();
}

Vector2f Box::getPosition() { // Get position
	return box.getPosition();
}

RectangleShape Box::getSprite() // Get rectangleShape
{
	return box;
}

void Box::CheckCollision(Creature& newCreature)
{
	// Check if creature is intersecting the box
	if (newCreature.getGlobalBounds().intersects(box.getGlobalBounds()))
	{
		// Touching top of box
		if (newCreature.position.y <= box.getPosition().y && (newCreature.position.x > box.getPosition().x + 5 || newCreature.position.x < box.getPosition().x - 5 + xSize + 1 * 60))
		{
			newCreature.position.y = box.getPosition().y - 84.0f;
			newCreature.updatePosition();
		}
		// Touching bottom of box
		if (newCreature.position.y > box.getPosition().y && (newCreature.position.x > box.getPosition().x + 5 || newCreature.position.x < box.getPosition().x - 5 + xSize + 1 * 60))
		{
			newCreature.position.y = box.getPosition().y + 60.0f;
			newCreature.updatePosition();
		}
		// If out of box in both x-axis directions
		if (newCreature.position.x < box.getPosition().x || newCreature.position.x > box.getPosition().x + xSize + 1 * 60)
		{
			// Do nothing
		}
	}
}