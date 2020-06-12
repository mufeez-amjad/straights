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
	this->_gameData->_activeRound = true;

	for (int suit = CLUB; suit < SUIT_COUNT; ++suit) {
		for(int rank = ACE; suit < RANK_COUNT; ++ rank) {
			this->_gameData->_deck[(13*suit) + rank] = new Card((Suit)suit, (Rank)rank);
		}
	}

	this->_gameData->_validMoves.push_back(this->_gameData->_deck[13*3 + 6]);

	shuffle(this->_gameData->_deck);

	int i = 0;
	while(this->_gameData->_deck[i] != this->_gameData->_validMoves[0]) ++i;

	this->_gameData->_currentPlayer = i/13;
}

Game::~Game()
{
	if (this->_gameData != NULL) {
		for (int i=0; i < CARD_COUNT; ++i) {
			delete this->_gameData->_deck[i];
		}
	}
}

Game::Game(const Game& g)
{
	this->_gameData = new GameData();
	this->_gameData->_playing = g._gameData->_playing;
	this->_gameData->_activeRound = g._gameData->_activeRound;
	this->_gameData->_currentPlayer = g._gameData->_currentPlayer;
	this->_gameData->_validMoves = g._gameData->_validMoves;

	for (int i = 0; i < CARD_COUNT; ++i) {
		this->_gameData->_deck[i] = new Card(*g._gameData->_deck[i]);
	}

	for (int i = 0; i < PLAYER_COUNT; ++i) {
		this->_gameData->_players[i].score = g._gameData->_players[i].score;
		this->_gameData->_players[i].points = g._gameData->_players[i].points;
		if (g._gameData->_players[i].player->getType() == 'h'){
			this->_gameData->_players[i].player = new Human(*g._gameData->_players[i].player);
		} else {
			this->_gameData->_players[i].player = new Computer(*g._gameData->_players[i].player);
		}
	}
}

Game& Game::operator=(const Game& g)
{
	Game g_copy = Game(g);

	GameData* temp_gameData = this->_gameData;
	this->_gameData = g_copy._gameData;
	g_copy._gameData = temp_gameData;

	return *this;
}

Game::Game(Game && g)
{
	this->_gameData = NULL;

	GameData* temp_gameData = this->_gameData;
	this->_gameData = g._gameData;
	g._gameData = temp_gameData;
}

Game& Game::operator=(Game && g)
{
	GameData* temp_gameData = this->_gameData;
	this->_gameData = g._gameData;
	g._gameData = temp_gameData;

	return *this;
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

		if (this->_gameOver())
			this->_gameData->_playing = false;
	}

	// declare winner
}

void Game::_playRound(void)
{
	this->_shuffleDeck();
	this->_printDeck();

	while(this->_gameData->_activeRound) {
		std::cerr << "round loop.\n";

		this->_playTurn(); // TODO: implement

		this->_updateActivePlayer();

		if (this->_roundOver())
			this->_gameData->_activeRound = false;
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

		this->_gameData->_players[i].points = 0;
		this->_gameData->_players[i].score = 0;
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

bool Game::_gameOver(void)
{
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if (this->_gameData->_players[i].score >= 80)
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
	this->_gameData->_currentPlayer %= 4;
}

void Game::_playTurn(void)
{
	std::cerr << "ERROR: _playTurn unimplemented.\n";
}
