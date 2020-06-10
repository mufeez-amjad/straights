#ifndef _GAME_
#define _GAME_

#include "Player.h";
#include "Card.h";

struct PlayerRecord {
	int score; // round accumulator
	int points;
	Player* player;
};

class Game {
	public:
		static Game* instance(){
			return &_game;
		}

		void turn();

	private:
		Game();

		bool _isValidTurn(Card*);
		void _playTurn(Card*);
		void _discardTurn(Card*);
		void _endRound();
		void _quit();
		void _humanToComputer(Player&);

		static Game _game;

		PlayerRecord _players[];
		PlayerNumber _currentTurn;
		Card* _deck[];
		Card* _validMoves[];
};

#endif
