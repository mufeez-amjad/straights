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

		void _printDeck(void); // TODO: move to private

	private:
		Game();

		~Game();

		void _playRound(void);

		void _updateActivePlayer(void);

		bool _gameOver(void);

		void _shuffleDeck(void);

		void _invitePlayers(void);

		void _playTurn(void);

		bool _roundOver(void);

		bool _isValidTurn(Card*);

		void _playTurn(Card*);

		void _discardTurn(Card*);

		void _endRound();

		void _quit();

		void _humanToComputer(Player&);

		// _game singleton instance
		static Game _game;

		GameData* _gameData;
};

#endif
