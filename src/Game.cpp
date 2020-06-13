#include "Game.h"
#include "Shuffle.h"
#include "Human.h"
#include "Computer.h"

#include <unordered_set>
#include <cassert>

// Create singleton instance
Game Game::_game;

Game::Game()
{
	this->_gameData = new GameData();

	for (int suit = CLUB; suit != SUIT_COUNT; suit++) {
		for (int rank = ACE; rank != RANK_COUNT; rank++) {
			this->_gameData->_deck[(RANK_COUNT*suit) + rank] = new Card((Suit)suit, (Rank)rank);
			this->_gameData->_table[(RANK_COUNT*suit) + rank] = nullptr;
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
		for (int i = 0; i < CARD_COUNT; ++i)
			delete this->_gameData->_deck[i];

		for (int i = 0; i < PLAYER_COUNT; ++i)
			delete this->_gameData->_players[i].player;
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
}

void Game::_playRound(void)
{
	std::cerr << "Unshuffled Deck \n";
	this->_printDeck();
	this->_shuffleDeck();
	std::cerr << "Shuffled Deck \n";
	this->_printDeck();

	for (int i = 0; i < PLAYER_COUNT; ++i) {
		this->_gameData->_players[i].player->setHand(
			this->_gameData->_deck[RANK_COUNT*i]
		);
	}

	this->_addValidMove(&Card(CLUB, SEVEN));
	this->_addValidMove(&Card(DIAMOND, SEVEN));
	this->_addValidMove(&Card(HEART, SEVEN));
	this->_addValidMove(&Card(SPADE, SEVEN));

	int i = 0;
	while(this->_gameData->_deck[i]->getRank() != SEVEN || this->_gameData->_deck[i]->getSuit() != SPADE) { ++i; }

	this->_gameData->_currentPlayer = i/RANK_COUNT;

	std::cout << "A new round begins. It's player " << this->_gameData->_currentPlayer+1 << "'s turn to play.\n";

	while(this->_gameData->_activeRound) {
		std::cerr << "round loop.\n";

		this->_playTurn();

		this->_updateActivePlayer();

		if (this->_roundOver())
			this->_gameData->_activeRound = false;
	}
	this->_scoreRound();
}

void Game::_scoreRound(void)
{
	for (int i = 0; i < PLAYER_COUNT; i++) {
		int score = this->_getPlayer(i).score;
		int points = this->_getPlayer(i).points;

		std::cout << "Player " << i+1 << "'s discards: " << "\n";

		std::cout << "Player " << i+1 << "'s score: "
		          << score << " + " << points
		          << " = " << score + points << "\n";

		this->_getPlayer(i).score = score + points;
		this->_getPlayer(i).points = 0;
	}
}

void Game::_shuffleDeck(void)
{
	shuffle(this->_gameData->_deck);
}

bool Game::_gameOver(void)
{
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if (this->_gameData->_players[i].score >= TARGET_SCORE) {
			std::cout << "Player " << i+1 << " wins!\n";
			return true;
		}
	}
	return true; // return false;
}

bool Game::_roundOver(void)
{
	std::cerr << "ERROR: _roundOver unimplemented.\n";
	return false; // TODO: implement
}

void Game::_updateActivePlayer(void)
{
	this->_gameData->_currentPlayer++;
	this->_gameData->_currentPlayer %= PLAYER_COUNT;
}

PlayerRecord& Game::_getCurrentPlayer(void)
{
	return this->_gameData->_players[this->_gameData->_currentPlayer];
}

PlayerRecord& Game::_getPlayer(int playerNumber)
{
	assert(playerNumber < PLAYER_COUNT);
	return this->_gameData->_players[playerNumber];
}

void Game::_printHumanPrompt(std::vector<Card*>& hand)
{
	std::cout << "Cards on the table:\n";
	std::cout << "Clubs:" << "\n";
	std::cout << "Diamonds:" << "\n";
	std::cout << "Hearts:" << "\n";
	std::cout << "Spades:" << "\n";
	std::cout << "Your hand:" << "\n";
	// iterate through hand and compare agains _gameData_validMoves, this is redundant
	// since we also calculate playerLegalPlays, but need to print legal plays in deck-order
	//  - pass in reference to empty playerLegalPlays and populate it here while printing legal
	//    plays in a loop
	//  - complicates logic since computers will not print this, so will still need a
	//    separate _calculatePlayerLegalPlays method (or maybe a faster calculate first legal move?)
	std::cout << "Legal plays:" << "\n";
}

std::unordered_set<int> Game::_calculatePlayerLegalPlays(std::vector<Card*>& hand)
{
	std::unordered_set<int> playerLegalPlays;
	for (auto& card: hand) {
		if (this->_gameData->_validMoves.find(card->getHash()) != this->_gameData->_validMoves.end()) {
			playerLegalPlays.emplace(card->getHash());
			if (this->_getCurrentPlayer().player->getType() == 'c')
				break;
		}
	}
	return playerLegalPlays;
}

void Game::_playTurn(void)
{
	PlayerRecord& current = this->_getCurrentPlayer();
	if (current.player->getType() == 'h')
		this->_printHumanPrompt(current.player->hand);

	std::unordered_set<int> playerLegalPlays = this->_calculatePlayerLegalPlays(current.player->hand);

	Command c = current.player->playTurn(playerLegalPlays);
	switch (c.type) {
		case PLAY:
			this->_playCard(&c.card); // will play card & also needs to update valid moves
			break;
		case DISCARD:
			// update score, player has updated their own hand
			// need to track how many cards are discarded since #discarded + #on table == 52 --> round end
			this->_discardCard(&c.card);
			break;
		case DECK:
			this->_printDeck();
			break;
		case QUIT:
			this->~Game(); // TODO: check if we destruct or nuke program here
			break;
		case RAGEQUIT:
			this->_humanToComputer(current.player); // need to swap out human with computer copy
			break;
		case BAD_COMMAND: // TODO: figure out what to do here, player should not allow itself to send BAD_COMMAND or undefined enum
		default:
			std::cerr << "ERROR: BAD_COMMAND recieved.\n";
			break;
	}

}

// Gameplay command implementations
void Game::_playCard(Card* card)
{
	std::cerr << "playing card " << *card << "...\n";

	this->_addToTable(card);

	this->_removeValidMove(card);

	int hash = card->getHash();
	Rank rank = card->getRank();
	switch (rank) {
		case KING:
			this->_addValidMove(hash - 1);
			break;
		case ACE:
			this->_addValidMove(hash + 1);
			break;
		default:
			this->_addValidMove(hash + 1);
			this->_addValidMove(hash - 1);
			break;
	}

}

void Game::_discardCard(Card* card)
{
	std::cerr << "discarding card " << *card << "...\n";
}

void Game::_humanToComputer(Player* player)
{
	std::cerr << "converting player " << this->_gameData->_currentPlayer+1 << " to computer...\n";
}

// Valid Move Methods

void Game::_addValidMove(Card* card)
{
	this->_gameData->_validMoves.emplace(card->getHash());
}

void Game::_addValidMove(int hash)
{
	this->_gameData->_validMoves.emplace(hash);
}

void Game::_removeValidMove(Card* card)
{
	this->_gameData->_validMoves.erase(card->getHash());
}

void Game::_removeValidMove(int hash)
{
	this->_gameData->_validMoves.erase(hash);
}

// Table Methods

void Game::_addToTable(Card* card)
{
	this->_gameData->_table[card->getHash()] = card;
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
