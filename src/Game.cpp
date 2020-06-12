#include "Game.h"
#include "Shuffle.h"
#include "Human.h"
#include "Computer.h"

// Create singleton instance
Game Game::_game;

Game::Game()
{
	this->_gameData = new GameData();

	for (int suit = CLUB; suit != SUIT_COUNT; suit++) {
		for (int rank = ACE; rank != RANK_COUNT; rank++) {
			this->_gameData->_deck[(RANK_COUNT*suit) + rank] = new Card((Suit)suit, (Rank)rank);
		}
	}

	this->_invitePlayers();
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

		this->_gameData->_players[i].points = 0;
		this->_gameData->_players[i].score = 0;
	}
}

Game::~Game()
{
	if (this->_gameData != nullptr) {
		for (int i = 0; i < CARD_COUNT; ++i) {
			delete this->_gameData->_deck[i];
		}
		for (int i = 0; i < PLAYER_COUNT; ++i) {
			delete this->_gameData->_players[i].player;
		}
	}
}

Game* Game::instance(void)
{
	return &Game::_game;
}

void Game::play(void)
{

	this->_gameData->_playing = true;

	while(this->_gameData->_playing) {
		std::cerr << "game loop.\n";

		this->_gameData->_activeRound = true;
		this->_playRound();

		if (this->_gameOver())
			this->_gameData->_playing = false;
	}

	// declare winner
}

void Game::_playRound(void)
{
	std::cerr << "Unshuffled Deck \n"; 
	this->_printDeck();
	this->_shuffleDeck();
	std::cerr << "Shuffled Deck \n";
	this->_printDeck();

	// for (int i = 0; i < PLAYER_COUNT; ++i) {
	// 	this->_gameData->_players[i].player->setHand(
	// 		this->_gameData->_deck[RANK_COUNT*i]
	// 	);
	// }

	int i = 0;
	while(this->_gameData->_deck[i]->getRank() != SEVEN ||
			this->_gameData->_deck[i]->getSuit() != SPADE) ++i;
	this->_gameData->_currentPlayer = i/RANK_COUNT;

	std::cout << "A new round begins. It's player " << this->_gameData->_currentPlayer+1 << "'s turn to play.\n";

	while(this->_gameData->_activeRound) {
		std::cerr << "round loop.\n";

		this->_playTurn(); // TODO: implement

		this->_updateActivePlayer();

		if (this->_roundOver())
			this->_gameData->_activeRound = false;
	}
}


void Game::_shuffleDeck(void)
{
	shuffle(this->_gameData->_deck);
}

void Game::_printDeck(void)
{
	for (int i = 0; i < SUIT_COUNT; i++) {
		for (int j = 0; j < RANK_COUNT; j++) {
			std::cout << *(this->_gameData->_deck[(RANK_COUNT * i) + j]);
			if (j != 12)
				std::cout << " ";
			else
				std::cout << "\n";
		}
	}
}

bool Game::_gameOver(void)
{
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if (this->_gameData->_players[i].score >= TARGET_SCORE)
			return true;
	}
	return true; // return false;
}

bool Game::_roundOver(void)
{
	std::cerr << "ERROR: _roundOver unimplemented.\n";
	return true; // TODO: implement
}

void Game::_updateActivePlayer(void)
{
	this->_gameData->_currentPlayer++;
	this->_gameData->_currentPlayer %= PLAYER_COUNT;
}

void Game::_playTurn(void)
{
	std::cerr << "ERROR: _playTurn unimplemented.\n";
}
