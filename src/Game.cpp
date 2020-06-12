#include "Game.h"
#include "Shuffle.h"
#include "Human.h"
#include "Computer.h"

// Create singleton instance
Game Game::_game;

Game::Game()
{
	this->_gameData = new GameData();
	this->_gameData->_playing = true;
}

Game* Game::instance(void)
{
	return &Game::_game;
}

void Game::play(void)
{
	this->_invitePlayers();

	while(this->_gameData->_playing) {
		std::cerr << "game loop.\n";
		break;
	}
}

void Game::_invitePlayers(void)
{
	std::string choice;
	for (int i = 0; i < PLAYER_COUNT; i++) {
		std::cout << "Is player " << i + 1 << " a human (h) or a computer (c)?\n";

		while (std::cin >> choice && choice != "h" && choice != "c") {}

		if (choice == "h")
			this->_gameData->_players[i].player = new Human();
		else
			this->_gameData->_players[i].player = new Computer();
	}
}
