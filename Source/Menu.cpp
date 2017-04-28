#include "Menu.h"

Menu::Menu(Pacman& playerOne, Pacman& playerTwo, Ghost& ghostOne, Ghost& ghostTwo, vector<Point>& pointVector, Scoreboard& newScoreboard, Music& newSong)
{
	// Save link to players
	player1 = &playerOne;
	player2 = &playerTwo;
	ghost1 = &ghostOne;
	ghost2 = &ghostTwo;
	points = &pointVector;
	scoreboard = &newScoreboard;

	// Create menu background
	menuBackground.setPosition(Vector2f(menuOffsetX, menuOffsetY));
	menuBackground.setSize(Vector2f(menuSizeX, menuSizeX));
	menuBackground.setFillColor(Color::Color(0,0,0,220));

	// Loading sound effects
	buffer1.loadFromFile("sfx/smb_pause.wav");
	buffer2.loadFromFile("sfx/smb_coin.wav");
	buffer3.loadFromFile("sfx/smb_kick.wav");
	buffer4.loadFromFile("sfx/smb2_bonus_chance_win.wav");
	buffer5.loadFromFile("sfx/smb2_bonus_chance_win.wav");

	open.setBuffer(buffer1);
	change.setBuffer(buffer2);
	cycle.setBuffer(buffer3);
	end.setBuffer(buffer4);
	start.setBuffer(buffer5);

	// Load font
	emulogic.loadFromFile("misc/emulogic.ttf");

	// Set default cursor position
	cursorPosition = 60;

	// Save link to music
	song = &newSong;

	// style menu items
	cursor.setFont(emulogic);
	cursor.setCharacterSize(fontSize);
	cursor.setFillColor(sf::Color::White);
	cursor.setString(">");

	resume.setFont(emulogic);
	resume.setCharacterSize(fontSize);
	resume.setFillColor(sf::Color::White);
	resume.setString("Resume");

	restart.setFont(emulogic);
	restart.setCharacterSize(fontSize);
	restart.setFillColor(sf::Color::White);
	restart.setString("Restart");

	music.setFont(emulogic);
	music.setCharacterSize(fontSize);
	music.setFillColor(sf::Color::White);
	music.setString("Music on");

	sounds.setFont(emulogic);
	sounds.setCharacterSize(fontSize);
	sounds.setFillColor(sf::Color::White);
	sounds.setString("Sound on");

	quit.setFont(emulogic);
	quit.setCharacterSize(fontSize);
	quit.setFillColor(sf::Color::White);
	quit.setString("Quit");
}

void Menu::displayMenu(RenderWindow& newWindow, float dt) // Display the menu
{
	// Slow down cursor speed
	cursorTimer += dt;
	if (cursorTimer > cursorDelay)
		cursorTimer = 0;

	// Show menu when hit escape on keyboard
	if (Keyboard::isKeyPressed(Keyboard::Escape) && !showMenu && cursorTimer == 0)
	{
		open.play();
		menuItem = 0;
		showMenu = true;
	}
	// Hide menu when hit escape on keyboard
	else if(Keyboard::isKeyPressed(Keyboard::Escape) && showMenu && cursorTimer == 0)
		showMenu = false;
	
	if (showMenu)
	{
		song->pause();

		cursor.setPosition(Vector2f(20 + menuOffsetX, cursorPosition + menuOffsetY));
		resume.setPosition(Vector2f(80 + menuOffsetX, 60 + itemOffsetY * 0 + menuOffsetY));
		restart.setPosition(Vector2f(80 + menuOffsetX, 60 + itemOffsetY * 1 + menuOffsetY));
		music.setPosition(Vector2f(80 + menuOffsetX, 60 + itemOffsetY * 2 + menuOffsetY));
		sounds.setPosition(Vector2f(80 + menuOffsetX, 60 + itemOffsetY * 3 + menuOffsetY));
		quit.setPosition(Vector2f(80 + menuOffsetX, 60 + itemOffsetY * 4 + menuOffsetY));

		// Move cursor in menu
		if (Keyboard::isKeyPressed(Keyboard::Up) && cursorTimer == 0)
		{
			menuItem--; 
			cycle.play(); // Play sound
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && cursorTimer == 0)
		{
			menuItem++;
			cycle.play(); // Play sound
		}
		
		// Loop menu
		if (menuItem < 0)
			menuItem = lastItem;

		if (menuItem > lastItem)
			menuItem = 0;
		
		// When Enter is pressed on menu items
		if (Keyboard::isKeyPressed(Keyboard::Return) && cursorTimer == 0)
		{
			switch (menuItem)
			{
			case 0: // Resume
				showMenu = false;
				break;
			case 1: // Restart
				resetGame();
				break;
			case 2: // Music
				musicOn = !musicOn;
				break;
			case 3: // Sound
				soundOn = !soundOn;
				if(soundOn)
					for (auto& point : *points)
						point.soundOn = true;
				else
					for (auto& point : *points)
						point.soundOn = false;
				break;
			case 4: // Quit
				newWindow.close();
				break;
			}
			change.play(); // Play sound
		}

		// Checking sound settings
		if (musicOn)
			{song->play(); music.setString("Music on");}
		else 
			{song->stop(); music.setString("Music off");}

		if (soundOn) 
			sounds.setString("Sound on");
		else 
			sounds.setString("Sound off");

		// Update cursor position
		cursor.setPosition(Vector2f(40 + menuOffsetX, 60 + itemOffsetY * menuItem + menuOffsetY));

		// Draw menu in window
		newWindow.draw(menuBackground);
		newWindow.draw(resume);
		newWindow.draw(restart);
		newWindow.draw(music);
		newWindow.draw(sounds);
		newWindow.draw(quit);
		newWindow.draw(cursor);
	}
}

void Menu::endOfGame(RenderWindow& newWindow, float dt)
{
	// Make background
	menuEnd.setPosition(Vector2f(menuOffsetX - 20, menuOffsetY + 10));
	menuEnd.setSize(Vector2f(menuSizeX + 40, menuSizeX - 60));
	menuEnd.setFillColor(Color::Color(0, 0, 0, 220));

	// Set text
	endOfRound.setFont(emulogic);
	endOfRound.setCharacterSize(fontSize);
	endOfRound.setFillColor(sf::Color::White);

	// Set text positions
	endOfRound.setPosition(Vector2f(20 + menuOffsetX, 60 + itemOffsetY * 0 + menuOffsetY));
	restart.setPosition(Vector2f(80 + menuOffsetX, 60 + itemOffsetY * 2 + menuOffsetY));
	quit.setPosition(Vector2f(80 + menuOffsetX, 60 + itemOffsetY * 3 + menuOffsetY));

	if (!showMenu && musicOn)
		end.play();

	showMenu = true;

	// Create new header based on win condition
	if (player1->hearts > player2->hearts)
		endOfRound.setString("Player 2 died!\nPlayer 1 wins!");

	else if (player1->hearts > 0 && player2->hearts > 0)
	{
		if(player1->score > player2->score)
			endOfRound.setString("Player 1 wins!\nPlayer 2 lost");
		else
			endOfRound.setString("Player 2 wins!\nPlayer 1 lost");
	}

	else
		endOfRound.setString("Player 1 died!\nPlayer 2 wins!");


	if (showMenu)
	{
		// Slow down cursor speed
		cursorTimer += dt;
		if (cursorTimer > cursorDelay)
			cursorTimer = 0;

		song->pause();

		// Move cursor in menu
		if (Keyboard::isKeyPressed(Keyboard::Up) && cursorTimer == 0)
		{
			menuItem--;
			cycle.play(); // Play sound
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) && cursorTimer == 0)
		{
			menuItem++;
			cycle.play(); // Play sound
		}

		// Loop menu
		if (menuItem < 2)
			menuItem = 3;

		if (menuItem > 3)
			menuItem = 2;

		// When Enter is pressed on menu items
		if (Keyboard::isKeyPressed(Keyboard::Return) && cursorTimer == 0)
		{
			switch (menuItem)
			{
			case 2: // Restart
				resetGame();
				showMenu = false;
				break;
			case 3: // Quit
				newWindow.close();
				break;
			}
			change.play(); // Play sound
		}

		// Update cursor position
		cursor.setPosition(Vector2f(40 + menuOffsetX, 60 + itemOffsetY * menuItem + menuOffsetY));

	}

	// Draw menu
	newWindow.draw(menuEnd);
	newWindow.draw(endOfRound);
	newWindow.draw(cursor);
	newWindow.draw(restart);
	newWindow.draw(quit);
}

void Menu::resetGame()
{
	player1->reset();
	player2->reset();
	ghost1->reset();
	ghost2->reset();
	scoreboard->pointsTaken = 0;

	for (auto& point : *points)
	{
		point.reset();
	}

	song->play();

	showMenu = false;
}