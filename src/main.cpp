#include <iostream>

#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game = Game::instance();
	game->play();
	return 0;
}
