#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <array>
#include <time.h>
#include <Windows.h>
#include "animation.h"
#include "Box.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Menu.h"
#include "Point.h"
#include "Scoreboard.h"
using namespace sf;
using namespace std;


// Size of map
const int H = 14;
const int W = 20;

// Map editor
String TileMap[H] = 
{
	"                    ",
	"t                T  ",
	"   Oooo      oooO   ",
	"fffffff      fffffff",
	"                    ",
	"      oooooooo      ",
	" Oo   bbbbbbbb   oO ",
	"bbb              bbb",
	"                    ",
	" oooooo      oooooo ",
	"bbbbbbb      bbbbbbb",
	"t                T  ",
	"   oooooooooooooo   ",
	"fffffffffffffffffffff"
};



int main()
{
	// Hide console window
	FreeConsole();

	srand(time(NULL));


	// Create new window
	RenderWindow window(VideoMode(1080, 840), "Pacman Battle", Style::Close | Style::Titlebar); // Create new window
	window.setFramerateLimit(30); // Limit framerate


	// Set background
	Texture backgroundTexture; // Create new texture
	backgroundTexture.loadFromFile("gfx/tinywings_bg.jpg"); // Load texture
	Sprite background; // Create new sprite
	background.setTexture(backgroundTexture); // Set texture to backgrund sprite


	// Load spritesheet
	Texture spriteSheet; // Create new texture
	spriteSheet.loadFromFile("gfx/pacman_sprites_full.png"); // Load texture
	spriteSheet.setSmooth(1); // Smooth texture
	Sprite mapElement(spriteSheet); // Set texture to mapElement sprite


	// Create boxes & floors
	Box floor(20, 1, -1, 13);
	Box box1(7, 1, -1, 10);
	Box box2(7, 1, 12, 10);
	Box box3(3, 1, -1, 7);
	Box box4(3, 1, 16, 7);
	Box box5(8, 1, 5, 6);
	Box box6(7, 1, -1, 3);
	Box box7(7, 1, 12, 3);


	// Create players
	Pacman playerOne(Vector2f(990, 696), 0);
	Pacman playerTwo(Vector2f(10, 696), 1);


	// Create ghosts
	Ghost ghost1(Vector2f(-84.0f, 96.0f));
	Ghost ghost2(Vector2f(-84.0f, 96.0f));


	// Create point vector
	std::vector<Point> points;

	// Create points from map editor
	for (int i = 0; i<H; i++){
		for (int j = 0; j<W; j++)
		{
			if (TileMap[i][j] == 'o')
				points.push_back(Point(sf::Vector2f(j, i), false));	// Small circle
			if (TileMap[i][j] == 'O')
				points.push_back(Point(sf::Vector2f(j, i), true)); // Large circle
		}
	}

	// Create point object
	Point p0(sf::Vector2f(500, 500), true);

	// Get max number of points from vector
	int maxPoints = points.size();


	// Fps counter
	Font emulogic; // Set font
	emulogic.loadFromFile("misc/emulogic.ttf");

	Text fpsCount;
	fpsCount.setFont(emulogic);
	fpsCount.setCharacterSize(10);
	fpsCount.setFillColor(sf::Color::Black);
	fpsCount.setPosition(Vector2f(20, 20));


	// Set up music
	Music music;

	switch (rand() % 3) // Random song
	{
	case 0:
		music.openFromFile("sfx/music.ogg");
		break;
	case 1:
		music.openFromFile("sfx/music2.ogg");
		break;
	case 2:
		music.openFromFile("sfx/music3.ogg");
		break;
	default:
		music.openFromFile("sfx/music3.ogg");
		break;
	}

	music.setVolume(50.0f); // Set music volume
	music.setLoop(true); // Loop music
	music.play(); // Start playing


	// Create scoreboard
	Scoreboard scoreboard(window, playerOne, playerTwo);


	// Create menu
	Menu newMenu(playerOne, playerTwo, ghost1, ghost2, points, scoreboard, music);


	// Clock / timers
	Clock clock;
	float dt = 0.0f;
	float loopTime = 0.0f;
	int fps = 0;


	while (window.isOpen())
	{
		// fps counter for debugging
		loopTime += dt; // Get loops pr second

		if (loopTime >= 1.0f)
		{
			if (fps < 25)
			{
				fpsCount.setFillColor(sf::Color::Red);
				fpsCount.setString(to_string(fps) + " fps LOW FRAMERATE < 25"); // Print fps to window
			}
			else
			{
				fpsCount.setFillColor(sf::Color::Black);
				fpsCount.setString(to_string(fps) + " fps"); // Print fps to window
			}

			loopTime = 0.0f; // Reset looptime
			fps = 0; // Reset fps counter
		}
		else
			fps++; // update fps counter

		
		dt = clock.restart().asSeconds(); // Delta time


		// Check if close or escape button is pressed -> close window
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == Event::Closed)
				window.close();
		}


		// Controls
		playerOne.input(dt, newMenu);
		playerTwo.input(dt, newMenu);


		// Move ghosts
		ghost1.move(playerOne, playerTwo, dt, newMenu);
		ghost2.move(playerOne, playerTwo, dt, newMenu);


		// Hit detection on boxes
		floor.CheckCollision(playerOne);
		box1.CheckCollision(playerOne);
		box2.CheckCollision(playerOne);
		box3.CheckCollision(playerOne);
		box4.CheckCollision(playerOne);
		box5.CheckCollision(playerOne);
		box6.CheckCollision(playerOne);
		box7.CheckCollision(playerOne);

		floor.CheckCollision(playerTwo);
		box1.CheckCollision(playerTwo);
		box2.CheckCollision(playerTwo);
		box3.CheckCollision(playerTwo);
		box4.CheckCollision(playerTwo);
		box5.CheckCollision(playerTwo);
		box6.CheckCollision(playerTwo);
		box7.CheckCollision(playerTwo);

		floor.CheckCollision(ghost1);
		box1.CheckCollision(ghost1);
		box2.CheckCollision(ghost1);
		box3.CheckCollision(ghost1);
		box4.CheckCollision(ghost1);
		box5.CheckCollision(ghost1);
		box6.CheckCollision(ghost1);
		box7.CheckCollision(ghost1);

		floor.CheckCollision(ghost2);
		box1.CheckCollision(ghost2);
		box2.CheckCollision(ghost2);
		box3.CheckCollision(ghost2);
		box4.CheckCollision(ghost2);
		box5.CheckCollision(ghost2);
		box6.CheckCollision(ghost2);
		box7.CheckCollision(ghost2);


		// Check collision between players and ghosts
		playerOne.CheckCollision(ghost1);
		playerOne.CheckCollision(ghost2);
		playerTwo.CheckCollision(ghost1);
		playerTwo.CheckCollision(ghost2);
		

		// Draw everything on screen
		window.clear(Color::White); // Clear screen
		window.draw(background); // Draw background
	
		// Draw points and check for collisions
		for (auto& point : points) 
		{
			auto& sprite = point.getSprite();
			window.draw(sprite);
			point.checkCollision(playerOne, playerTwo, scoreboard, dt);
		}
		window.draw(p0.getSprite());
		
		// Draw ghosts
		window.draw(ghost1.getSprite());
		window.draw(ghost2.getSprite());
		
		// Draw map from map editor
		for (int i = 0; i<H; i++)
			for (int j = 0; j<W; j++)
			{
				if (TileMap[i][j] == 'f') { // Floor
					mapElement.setTextureRect(IntRect(264, 601, 60, 60));
					mapElement.setPosition(j * 60 - 60, i * 60);
					window.draw(mapElement);
				}

				if (TileMap[i][j] == 'b') { // Boxes
					mapElement.setTextureRect(IntRect(180, 601, 60, 60));
					mapElement.setPosition(j * 60 - 60, i * 60);
					window.draw(mapElement);
				}

				if (TileMap[i][j] == 't') { // Tube left
					mapElement.setTextureRect(IntRect(0, 679, 180, 120));
					mapElement.setPosition(j * 60 - 60, i * 60);
					window.draw(mapElement);
				}

				if (TileMap[i][j] == 'T') { // Tube right
					mapElement.setTextureRect(IntRect(195, 679, 180, 120));
					mapElement.setPosition(j * 60 - 60, i * 60);
					window.draw(mapElement);
				}
				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;
			}

		// Draw players
		window.draw(playerOne.getSprite());
		window.draw(playerTwo.getSprite());
		
		// Draw scoreboard
		scoreboard.displayScore(playerOne, playerTwo);

		// End game if...
		if (scoreboard.pointsTaken >= maxPoints || playerOne.hearts <= 0 || playerTwo.hearts <= 0)
			newMenu.endOfGame(window, dt);
		else
			newMenu.displayMenu(window, dt);

		// Display window
		window.display();

	}
	return 0;
}
