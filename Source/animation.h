#pragma once
#include <sfml/graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
using namespace sf;

class Animation
{
	private:
		Vector2u imageCount; // How many images in the animation?
		Vector2u currentImage; // Current frame
		float totalTime;
		float switchTime; // Framerate

	public:
		Animation();
		Animation(Texture* texture, Vector2u images, float framerate);
		void Update(int row, Vector2u startEnd, float dt);
		IntRect uvRect;
};