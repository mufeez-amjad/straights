#ifndef _GAME_
#define _GAME_

#include <iostream>

#include "GamePimpl.h"
#include "Command.h"

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
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void play(void);
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

	private:
		Game();
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void _turn(Command);
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		bool _isValidTurn(Card*);
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void _playTurn(Card*);
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void _discardTurn(Card*);
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void _endRound();
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void _quit();
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void _humanToComputer(Player&);
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		// _game singleton instance
		static Game _game;

		GameData* _gameData;
};

#endif
