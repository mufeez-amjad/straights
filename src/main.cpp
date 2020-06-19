#include <iostream>
#include <random>
#include <chrono>

#include "Game.h"

int main(int argc, char* argv[])
{
	// global variable seed in Deck.h
	if (argc > 1) {
		seed = std::stoi(std::string(argv[1]));
	} else {
		// If no seed provided in argv, use Mersenne Twister pseudorandom
		// number generator seeded by the time since epoch to generate a
		// pseudorandom int value for seed.
		unsigned long long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 seed_generator(time);
		seed = seed_generator();
	}

	Game* game = Game::instance();
	game->play();
	return 0;
}
