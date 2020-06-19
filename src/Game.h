#ifndef _GAME_
#define _GAME_

#include <iostream>

#include "GamePimpl.h"
#include "Command.h"

#define TARGET_SCORE 80

//============================================================================
// Game is a singleton class which represents a single instance of the game
// straights with the following specification fields:
// 
// The private implementation of Game's data members _gameData:
//		bool _playing		- Whether the game is being played. Used to 
//							  determine whether a human player has asked to
//							  quit the game during an active round
//		bool _activeRound	- Whether a round of straights is being played.
//							  Updated after scoring each round.
//		int _currentPlayer	- The number of the current player [1,2,3,4]. 
//							  Updated after every turn by incrementing.
//		int _cardsInPlay	- The number of cards from the deck which have
//							  been played. Initialized to CARD_COUNT and
//							  decremented each time a card moves from a
//							  player's hand to the table
//		std::unordered_set<int> _validMoves;
//							- Initialized to [7S], or more specifically an int
//							  that maps to it and updated based on the cards 
//							  in play on the table after every turn
//		Deck* _deck			- An instance of the Deck class, stores the
//							  CARD_COUNT number of cards for the game.
//		CardTable* _table	- An instance of the CardTable class, stores the 
//							  current cards in play.
//		PlayerRecord _players[PLAYER_COUNT] - Array of PlayerRecord structs
//			int score		- Accumulates the total score of a player over 
//							  multiple rounds Modified after every round by 
//							  the game class for all players.
//			int points		- Stores the points for a player during a specific
//							  round. Modified everytime the player discards by
//							  the game class.
//			Player* player	- An instance of the Player class for each player.
// 
//============================================================================


class Game
{
	public:
		static Game* instance();
			// returns: the singleton instance of Game class

		void play(void);
			// modifies: Player members hand's, scores, as well as the set
			//           of valid moves as the game progresses until a winner
			//           is declared

		// Prevent copies of singleton instance
		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

	private:
		Game();
		~Game() noexcept;

		// Start and end of game methods =====================================
		void _invitePlayers(void);
			// modifies: The Player members are instantiated as Game recieves
			//           instructions from std::cin as to whether or not each
			//           Player is an instance of Human or of Computer.
			//           A prompt is written to std::cout for each player

		bool _gameOver(void);
			// returns: true if the game is over, or false if the game is still
			//          running

		void _declareWinner(void);
			// modifies: The winning player(s) and their scores are written
			//           to std::cout

		void _quitGame(void);
			// modifies: Changes the game state to indicate the game has ended

		// Round and helper methods ===========================================
		void _playRound(void);
			// modifies: Adds cards to the CardTable instance, and removes cards
			//           from Player's hands as they play. Writes updates on the
			//           game state to std::cout.

		void _scoreRound(void);
			// modifies: Adds to each Player's score accumulator at the end of
			//           a round to reflect their updated score.

		bool _roundOver(void);
			// returns: true if the round is over (all cards have been played or
			//          discarded), and false otherwise.

		// Player helper methods ==============================================
		void _updateActivePlayer(void);
			// modifies: Alters the game state to set the current player to be
			//           the next player.

		PlayerRecord& _getCurrentPlayer(void);
			// returns: The current player

		PlayerRecord& _getPlayer(int);
			// returns: The player record associated with their number

		// Turn and helper methods ============================================
		void _playTurn(void);

		bool _queryTurn(PlayerRecord&, std::unordered_set<int>&);
			// returns:  true if the Player requests a valid move, otherwise
			//           returns false
			// ensures:  The current Player's hand to reflect their (valid)
			//           move, and updates the CardTable and set of valid
			//           moves once the player has played.

		void _printHumanPrompt(std::vector<Card*>&);
			// modifies: Writes a prompt to std::cout to inform human players
			//           of the current game state and list valid moves.

		std::unordered_set<int> _calculatePlayerLegalPlays(std::vector<Card*>&);
			// returns:  A set of all valid moves for the current player

		void _playCard(Card*);
			// ensures:  Adds the Card* parameter to the CardTable, and
			//           decrements the number of active cards by 1.

		void _discardCard(Card*);
			// ensures:  Adds the Card*'s value to the current player's score,
			//           and decrements the number of active cards by 1.

		void _humanToComputer(Player*);
			// requires: The Player* must be an instance of the Human ADT
			// ensures:  The instance of the current is replaced by a Computer
			//           instace having the same hand and score of the Human
			//           it replaces.

		void _quit();

		// Legal play methods =================================================
		void _addValidMove(Card*);
		void _addValidMove(int);
			// ensures:  The set of valid moves accounts for the Card*
			//           or the Card hash passed as an integer having
			//           been placed on the table.

		void _removeValidMove(Card*);
		void _removeValidMove(int);
			// ensures:  The set of valid moves does not contain the Card*
			//           or the Card* with the hash passed as an integer
			//           passed as the parameter.

		bool _isValidMove(Card*);
		bool _isValidMove(int);
			// returns:  true if the Card* or the hash of a Card passed as an
			//           integer is a valid move.

		void _makeSevensValidMoves(void);
			// ensures:  All sevens except for the seven of spades are added to
			//           the set of valid moves

		void _resetValidMoves(void);
			// ensures:  The set of valid moves is empty.

		// Singleton instance
		static Game _game;

		// Private implementation data
		GameData* _gameData;
};

#endif
