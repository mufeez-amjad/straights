#include <iostream>

#include "Game.h"
#include "Shuffle.h"

#include "Computer.h"

int main(int argc, char* argv[])
{
	// global variable seed in Shuffle.h
	if (argc > 1)
		seed = std::stoi(std::string(argv[1]));
	else
		seed = rand();

	Game* game = Game::instance();
	game->play();
	return 0;
}
