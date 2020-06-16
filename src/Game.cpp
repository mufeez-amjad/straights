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
			int index = (RANK_COUNT*suit) + rank;
			this->_gameData->_deck[index] = new Card((Suit)suit, (Rank)rank);
			this->_gameData->_table[index] = nullptr;
			this->_gameData->_orderedDeck[index] = nullptr;
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

		delete this->_gameData;
	}
}

void Game::_quitGame(void)
{
	this->_gameData->_playing = false;
}

Game* Game::instance(void)
{
	return &Game::_game;
}

void Game::play(void)
{

	this->_gameData->_playing = true;

	while(this->_gameData->_playing) {
		this->_gameData->_activeRound = true;
		this->_playRound();

		if (this->_gameOver())
			this->_gameData->_playing = false;
	}

	// If the game is over but a round is still active,
	// quit silently
	if (this->_gameData->_activeRound)
		return;

	this->_declareWinner();
}

void Game::_declareWinner(void)
{
	int minScore = this->_gameData->_players[0].score;
	for (int i = 1; i < PLAYER_COUNT; i++) {
		if (this->_gameData->_players[i].score < minScore)
			minScore = this->_gameData->_players[i].score;
	}
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if (this->_gameData->_players[i].score == minScore)
			std::cout << "Player " << i + 1 << " wins!\n";
	}
}

void Game::_playRound(void)
{
	// std::cerr << "Unshuffled Deck:\n";
	// this->_printDeck();

	this->_clearTable();
	this->_shuffleDeck();
	this->_resetValidMoves();

	// std::cerr << "Shuffled Deck \n";
	// this->_printDeck();

	for (int i = 0; i < PLAYER_COUNT; ++i) {
		this->_gameData->_players[i].player->setHand(
			&this->_gameData->_deck[RANK_COUNT*i]
		);
	}

	this->_gameData->_cardsInHand = CARD_COUNT;

	int i = 0;
	while(this->_gameData->_deck[i]->getRank() != SEVEN || this->_gameData->_deck[i]->getSuit() != SPADE) { ++i; }

	this->_gameData->_currentPlayer = i/RANK_COUNT;

	std::cout << "A new round begins. It's player " << this->_gameData->_currentPlayer + 1 << "'s turn to play.\n";

	while(this->_gameData->_activeRound && this->_gameData->_playing) {
		this->_playTurn();
		this->_updateActivePlayer();

		if (this->_roundOver())
			this->_gameData->_activeRound = false;
	}

	if (this->_gameData->_playing) { // TODO: verify
		this->_scoreRound();
		for (int i = 0; i < PLAYER_COUNT; i++) {
			this->_getPlayer(i).player->resetHand();
		}
	}
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
	for (int i = 0; i < CARD_COUNT; i++) {
		Card* card = this->_gameData->_deck[i];
		this->_gameData->_orderedDeck[card->getHash()] = card;
	}

	// std::cerr << "unshuffled deck:\n";
	// for (int i = 0; i < CARD_COUNT; i++)
	// 	std::cerr << *this->_gameData->_orderedDeck[i] << " ";
	// std::cerr << "\n";

}

bool Game::_gameOver(void)
{
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if (this->_gameData->_players[i].score >= TARGET_SCORE) {
			return true;
		}
	}
	return false;
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
			playerLegalPlays.insert(card->getHash());
			if (this->_getCurrentPlayer().player->getType() == PlayerType::COMPUTER)
				break;
		}
	}
	return playerLegalPlays;
}

bool Game::_queryTurn(PlayerRecord& current, std::unordered_set<int>& legalPlays)
{
	Command c;

	try {
		c = current.player->playTurn(legalPlays);
	} catch (Human::InvalidMoveException e) {
		std::cout << e.getMessage() << std::endl;
		return true;
	}

	switch (c.type) {
		case PLAY:
			std::cout << "Player " << this->_gameData->_currentPlayer + 1 << " plays " << c.card << ".\n";
			this->_playCard(this->_gameData->_orderedDeck[c.card.getHash()]);
			current.player->removeCard(this->_gameData->_orderedDeck[c.card.getHash()]);
			break;
		case DISCARD:
			std::cout << "Player " << this->_gameData->_currentPlayer + 1 << " discards " << c.card << ".\n";
			this->_discardCard(this->_gameData->_orderedDeck[c.card.getHash()]);
			break;
		case DECK:
			this->_printDeck();
			return true;
			break;
		case QUIT:
			this->_quitGame();
			break;
		case RAGEQUIT:
			std::cout << "Player " << this->_gameData->_currentPlayer + 1 << " ragequits. A computer will now take over.\n";
			this->_humanToComputer(current.player);
			// update valid turn
			return true;
			break;
		default:
			break;
	}
	// always done after breaking from switch
	return false;
}

void Game::_playTurn(void)
{
	PlayerRecord& current = this->_getCurrentPlayer();
	std::vector<Card*> hand = current.player->getHand();

	if (current.player->getType() == PlayerType::HUMAN) {
		this->_printHumanPrompt(hand);
	}

	bool requery = false;
	do {
		std::unordered_set<int> playerLegalPlays = this->_calculatePlayerLegalPlays(hand);
		// std::cerr << "playerLegalPlays: ";
		// for (auto& p: playerLegalPlays) {
		// 	std::cerr << Card(p) << " ";
		// }
		// std::cerr << "\n";
		requery = this->_queryTurn(current, playerLegalPlays);
	} while (requery);
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
			// no rank is higher than King
			this->_addValidMove(hash - 1);
			break;
		case ACE:
			// no rank is lower than Ace
			this->_addValidMove(hash + 1);
			break;
		default:
			this->_addValidMove(hash + 1);
			this->_addValidMove(hash - 1);
			break;
	}

	// after the 7 of spades has been played, all 7s are valid plays
	if (*card == Card(SPADE, SEVEN))
		this->_makeSevensValidMoves();
}

void Game::_discardCard(Card* card)
{
	this->_getCurrentPlayer().points += card->getRank() + 1;
	this->_gameData->_cardsInHand--;
}

void Game::_humanToComputer(Player* player)
{
	Player* currentPlayer = this->_getCurrentPlayer().player;
	Computer* computer = new Computer(*currentPlayer);
	delete currentPlayer;
	this->_gameData->_players[this->_gameData->_currentPlayer].player = computer;
}

// Valid Move Methods

void Game::_addValidMove(Card* card)
{
	this->_addValidMove(card->getHash());
}

void Game::_addValidMove(int hash)
{
	this->_gameData->_validMoves.emplace(hash);
}

void Game::_removeValidMove(Card* card)
{
	this->_removeValidMove(card->getHash());
}

void Game::_removeValidMove(int hash)
{
	this->_gameData->_validMoves.erase(hash);
}

bool Game::_isValidMove(Card* card)
{
	return this->_isValidMove(card->getHash());
}

bool Game::_isValidMove(int hash)
{
	return this->_gameData->_validMoves.find(hash) != this->_gameData->_validMoves.end();
}

void Game::_resetValidMoves(void)
{
	this->_gameData->_validMoves.clear();
	this->_addValidMove(Card(SPADE, SEVEN).getHash());
}

void Game::_makeSevensValidMoves(void)
{
	this->_addValidMove(Card(CLUB, SEVEN).getHash());
	this->_addValidMove(Card(DIAMOND, SEVEN).getHash());
	this->_addValidMove(Card(HEART, SEVEN).getHash());
}

// Table Methods

void Game::_addToTable(Card* card)
{
	this->_gameData->_table[card->getHash()] = card;
	this->_gameData->_cardsInHand--;
}

void Game::_clearTable(void)
{
	for (int i = 0; i < CARD_COUNT; i++)
		this->_gameData->_table[i] = nullptr;
}

void Game::_printTable(void)
{
	std::cout << "Cards on the table:\n";
	for (int i = 0; i < SUIT_COUNT; i++) {
		std::cout << Card::getName((Suit)i) << ":";
		for (int j = 0; j < RANK_COUNT; j++) {
			if (this->_gameData->_table[Card::hash((Suit)i, (Rank)j)] != nullptr)
				std::cout << " " << this->_gameData->_table[Card::hash((Suit)i, (Rank)j)]->getRank() + 1;
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
