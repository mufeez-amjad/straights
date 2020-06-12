#ifndef _GAME_
#define _GAME_

#include <iostream>

#include "GamePimpl.h"
#include "Command.h"

#define TARGET_SCORE 80

class Game {
	// Private Implementation for data members GameData
		// PlayerRecord _players[]
			// int score
			// int points
			// Player* player
		// PlayerNumber _currentTurn {ONE, TWO, THREE, FOUR}
		// Card* _deck[]
		// Card* _validMoves[];

	public:
		static Game* instance();

		void play(void);

	private:
		Game();

		~Game();

		// Start and end of game methods =====================================
		void _invitePlayers(void);

		bool _gameOver(void);

		// Round and helper methods ===========================================
		void _playRound(void);

		void _shuffleDeck(void);

		void _scoreRound(void);

		bool _roundOver(void);

		void _endRound();

		// Player helper methods ==============================================
		void _updateActivePlayer(void);

		PlayerRecord& _getCurrentPlayer(void);

		PlayerRecord& _getPlayer(int);

		// Turn and helper methods ============================================
		void _playTurn(void);

		void _printHumanPrompt(std::vector<Card*>&);

		std::unordered_set<Card*> _calculatePlayerLegalPlays(std::vector<Card*>&);

		void _playCard(Card*);

		void _discardCard(Card*);

		void _humanToComputer(Player*);

		void _printDeck(void);

		void _quit();

		// Singleton instance
		static Game _game;

		GameData* _gameData;
};

#endif
