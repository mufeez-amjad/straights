#ifndef _GAME_
#define _GAME_

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
		static Game* instance(){
			return &_game;
		}
			//requires:
			//throws:
			//modifies:
			//ensures:
			//returns:

		void turn(Command);
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

		static Game _game;
		GameData* _gameData;
};

#endif
