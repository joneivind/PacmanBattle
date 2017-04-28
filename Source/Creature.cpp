#include "Creature.h"

RectangleShape Creature::getSprite() // Get RectangleShape
{
	return creature;
}

void Creature::setPosition(Vector2f newPosition) // Set position of creature
{
	position = newPosition;
}

FloatRect Creature::getGlobalBounds() { // Get borders
	return creature.getGlobalBounds();
}

void Creature::updatePosition() // Set new position
{
	creature.setPosition(position);
}
