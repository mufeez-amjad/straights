#include <iostream>

#include "Game.h"

int main(void)
{
	std::cerr << "straights!\n";
	Game* game = Game::instance();
	game->play();
	return 0;
}
