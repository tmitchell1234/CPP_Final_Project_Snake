/*
	Tom Mitchell
	November 17, 2021
	C++ Final Project - Snake Game

	Please see the SourcesCited.docx document for
	references. I used two YouTube videos as a starting
	point for understanding the logic behind the game of
	"Snake" and for how to draw graphics using the SFML library.

	See ProjectDetails.docx for more technical information.

	CONTROLS:
		W - Move up
		A - Move left
		S - Move down
		D - Move right
		Escape - Close the game
*/

#include <iostream>
#include "game.h"

int main()
{
	// initialize game class object
	Game game;

	// Main game loop
	while (game.running())
	{
		// update
		game.update();

		// render
		game.render();
	}
}