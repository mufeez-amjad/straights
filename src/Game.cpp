#include "Game.h"
#include "Human.h"
#include "Computer.h"

#include <unordered_set>
#include <cassert>

// Create singleton instance
Game Game::_game;

Game::Game()
{
	this->_gameData = new GameData();
	this->_gameData->_deck = new Deck();
	this->_gameData->_table = new CardTable();

	this->_invitePlayers();
}

void Game::_invitePlayers(void)
{
	std::string choice;
	for (int i = 0; i < PLAYER_COUNT; i++) {
		std::cout << "Is player " << i + 1 << " a human (h) or a computer (c)?\n> ";

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

Game::~Game() noexcept
{
	if (this->_gameData != nullptr) {
		delete this->_gameData->_deck;
		delete this->_gameData->_table;

		for (int i = 0; i < PLAYER_COUNT; ++i)
			delete this->_getPlayer(i).player;
	}
	delete this->_gameData;
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
	this->_gameData->_table->clear();
	this->_gameData->_deck->shuffle();
	this->_resetValidMoves();

	for (int i = 0; i < PLAYER_COUNT; ++i)
		this->_gameData->_players[i].player->setHand(*this->_gameData->_deck, RANK_COUNT * i);

	this->_gameData->_cardsInPlay = CARD_COUNT;

	int i = 0;
	while(this->_gameData->_deck->at(i)->getRank() != SEVEN || this->_gameData->_deck->at(i)->getSuit() != SPADE) { ++i; }

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
		for (int i = 0; i < PLAYER_COUNT; i++)
			this->_getPlayer(i).player->resetHand();
	}
}

void Game::_scoreRound(void)
{
	for (int i = 0; i < PLAYER_COUNT; i++) {

		int score = this->_getPlayer(i).score;
		int points = this->_getPlayer(i).points;

		std::vector<Card*> discards = this->_getPlayer(i).player->getDiscards();

		std::cout << "Player " << i+1 << "'s discards:" << discards << '\n';

		std::cout << "Player " << i+1 << "'s score: "
		          << score << " + " << points
		          << " = " << score + points << "\n";

		this->_getPlayer(i).score = score + points;
		this->_getPlayer(i).points = 0;
	}
}

bool Game::_gameOver(void)
{
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if (this->_gameData->_players[i].score >= TARGET_SCORE)
			return true;
	}
	return false;
}

bool Game::_roundOver(void)
{
	return this->_gameData->_cardsInPlay == 0;
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
	std::cout << "Cards on the table:\n" << *this->_gameData->_table << "\n";
	std::cout << "Your hand:" << hand << "\n";
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
		std::cout << e.getMessage() << "\n";
		return true;
	}

	switch (c.type) {
		case PLAY:
			std::cout << "Player " << this->_gameData->_currentPlayer + 1 << " plays " << c.card << ".\n";
			this->_playCard(this->_gameData->_deck->lookup(c.card));
			current.player->removeCard(this->_gameData->_deck->lookup(c.card));
			break;
		case DISCARD:
			std::cout << "Player " << this->_gameData->_currentPlayer + 1 << " discards " << c.card << ".\n";
			this->_discardCard(this->_gameData->_deck->lookup(c.card));
			break;
		case DECK:
			std::cout << *this->_gameData->_deck << "\n";
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
		requery = this->_queryTurn(current, playerLegalPlays);
	} while (requery);
}

// Gameplay command implementations
void Game::_playCard(Card* card)
{
	this->_gameData->_table->addCard(card);
	this->_gameData->_cardsInPlay--;

	this->_removeValidMove(card);

	int hash = card->getHash();
	Rank rank = card->getRank();
	switch (rank) {
		case KING:
			// no rank is higher than King
			this->_addValidMove(hash - 1);
			break;
		case ACE:
			this->_addValidMove(hash + 1);
			// no rank is lower than Ace
			break;
		case SEVEN:
			if (card->getSuit() == SPADE){
				this->_addValidMove(Card(CLUB, SEVEN).getHash());
				this->_addValidMove(Card(DIAMOND, SEVEN).getHash());
				this->_addValidMove(Card(HEART, SEVEN).getHash());
			}
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
	this->_getCurrentPlayer().points += card->getValue();
	this->_gameData->_cardsInPlay--;
}

void Game::_humanToComputer(Player* player)
{
	assert(player->getType() == PlayerType::HUMAN);
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
