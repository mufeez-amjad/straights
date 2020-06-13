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
	std::cin.clear();
}

Game::~Game()
{
	if (this->_gameData != nullptr) {
		for (int i = 0; i < CARD_COUNT; ++i)
			delete this->_gameData->_deck[i];

		for (int i = 0; i < PLAYER_COUNT; ++i)
			delete this->_getPlayer(i).player;
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
			&this->_gameData->_deck[RANK_COUNT*i]
		);
	}

	this->_gameData->_cardsInHand = CARD_COUNT;

	this->_addValidMove(Card(CLUB, SEVEN).getHash());
	this->_addValidMove(Card(DIAMOND, SEVEN).getHash());
	this->_addValidMove(Card(HEART, SEVEN).getHash());
	this->_addValidMove(Card(SPADE, SEVEN).getHash());

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

		std::cout << "Player " << i+1 << "'s discards: " << this->_getPlayer(i).player->getDiscards() << '\n';

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
	return this->_gameData->_cardsInHand == 0;
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
	this->_printTable();
	std::cout << "Your hand: " << hand << "\n";
	std::cout << "Legal plays:";
	for (auto& c: hand) {
		if (this->_isValidMove(c))
			std::cout << " " << *c;
	}
	std::cout << "\n";
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
		this->_printHumanPrompt(current.player->_hand);

	std::unordered_set<int> playerLegalPlays = this->_calculatePlayerLegalPlays(current.player->_hand);

requery:
	Command c = current.player->playTurn(playerLegalPlays);
	switch (c.type) {
		case PLAY:
			this->_playCard(&c.card);
			current.player->removeCard(&c.card);
			break;
		case DISCARD:
			this->_discardCard(&c.card);
			break;
		case DECK:
			this->_printDeck();
			goto requery;
			break;
		case QUIT:
			this->~Game(); // TODO: check if we destruct or nuke program here
			break;
		case RAGEQUIT:
			this->_humanToComputer(current.player);
			break;
		case BAD_COMMAND:
		default:
			// undefined behaviour
			break;
	}

}

// Gameplay command implementations
void Game::_playCard(Card* card)
{
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
	this->_getCurrentPlayer().points += card->getRank() + 1;
	this->_gameData->_cardsInHand--;
}

void Game::_humanToComputer(Player* player)
{
	Player* currentPlayer = this->_getCurrentPlayer().player;
	Computer* computer = new Computer(currentPlayer);
	delete currentPlayer;
	this->_gameData->_players[this->_gameData->_currentPlayer].player = computer;
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

bool Game::_isValidMove(Card* card)
{
	return this->_gameData->_validMoves.find(card->getHash()) != this->_gameData->_validMoves.end();
}

bool Game::_isValidMove(int hash)
{
	return this->_gameData->_validMoves.find(hash) != this->_gameData->_validMoves.end();
}

// Table Methods

void Game::_addToTable(Card* card)
{
	this->_gameData->_table[card->getHash()] = card;
	this->_gameData->_cardsInHand--;
}

void Game::_printTable(void)
{
	std::cout << "Cards on the table:\n";
	for (int i = 0; i < SUIT_COUNT; i++) {
		std::cout << Card::getName((Suit)i) << ":";
		for (int j = 0; j < RANK_COUNT; j++) {
			if (this->_gameData->_table[Card::hash((Suit)i, (Rank)j)] != nullptr)
				std::cout << " " << *this->_gameData->_table[Card::hash((Suit)i, (Rank)j)];
		}
		std::cout << "\n";
	}
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
