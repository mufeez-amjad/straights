#include "Game.h"

// Create singleton instance
Game Game::_game;

Game::Game()
{
	this->_gameData = new GameData();
	this->_gameData->_playing = true;
}

Game* Game::instance(void)
{
	return &Game::_game;
}

void Game::play(void)
{
	while(this->_gameData->_playing) {
		std::cerr << "game loop.\n";
		break;
	}
}
