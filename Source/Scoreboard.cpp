#include "Scoreboard.h"

Scoreboard::Scoreboard(sf::RenderTarget& gameWindow, Pacman& Player1, Pacman& Player2) 
{
	// Store players and window
	m_player1 = &Player1;
	m_player2 = &Player2;
	m_renderer = &gameWindow;
}

void Scoreboard::displayScore()
{
	// Get score from players
	String playerOneScore = sf::String(std::to_string(m_player1->score));
	String playerTwoScore = sf::String(std::to_string(m_player2->score));

	Font font; // New font
	font.loadFromFile("misc/emulogic.ttf"); // Load from file

	// Create scoreboard text, player 1
	Text textPlayer_1; // New text
	textPlayer_1.setFont(font); // Set font
	textPlayer_1.setString("Player 1: " + playerOneScore + " points"); // set the string to display
	textPlayer_1.setCharacterSize(15); // In pixels, not points!
	textPlayer_1.setFillColor(Color::White); // Set the color
	textPlayer_1.setStyle(Text::Bold); // Set the text style	
	textPlayer_1.setPosition(600, 10); // Set position
									
	// Same as above, player 2
	Text textPlayer_2;
	textPlayer_2.setFont(font);
	textPlayer_2.setString("Player 2:" + playerTwoScore + " points");
	textPlayer_2.setCharacterSize(15);
	textPlayer_2.setFillColor(Color::White);
	textPlayer_2.setStyle(Text::Bold);
	textPlayer_2.setPosition(200, 10);
	
	// Draw scoreboard
	m_renderer->draw(textPlayer_1);
	m_renderer->draw(textPlayer_2);

}