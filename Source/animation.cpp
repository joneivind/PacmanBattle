#include "Animation.h"

Animation::Animation()
{};

Animation::Animation(Texture* texture, Vector2u images, float framerate) // Constructor
{
	imageCount = images;
	switchTime = framerate;
	totalTime = 0.0f;
	currentImage.x = 0;

	// Set size of single texture
	uvRect.width = texture->getSize().x / float(images.x);
	uvRect.height = texture->getSize().y / float(images.y);
}

void Animation::Update(int row, Vector2u startEnd, float dt) // Update animation
{
	currentImage.y = row; // Selected row in texture pack
	totalTime += dt; // add dt to total time

	if (totalTime >= switchTime) // Framerate of animation
	{
		totalTime -= switchTime; // Reset timer
		currentImage.x++; // go to next image

		if (currentImage.x > startEnd.y) // Go back to first image
			currentImage.x = startEnd.x;
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}