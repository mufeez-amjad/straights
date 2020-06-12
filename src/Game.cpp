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
	for (int s = CLUB; s != SUIT_COUNT; s++) {
		for (int r = ACE; r != RANK_COUNT; r++)
			this->_gameData->_deck[(13 * s) + r] = new Card((Suit)s, (Rank)r);
	}
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

		this->_gameData->_activeRound = true;
		this->_playRound();

		break;
	}
}

void Game::_playRound(void)
{
	this->_shuffleDeck();
	this->_printDeck();

	while(this->_gameData->_activeRound) {
		std::cerr << "round loop.\n";
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

void Game::_shuffleDeck(void)
{
	shuffle(this->_gameData->_deck);
}

void Game::_printDeck(void)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			std::cout << *(this->_gameData->_deck[(13 * i) + j]);
			if (j != 12)
				std::cout << " ";
			else
				std::cout << "\n";
		}
	}
}
