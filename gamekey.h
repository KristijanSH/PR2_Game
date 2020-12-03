#ifndef GAMEKEY_H
#define GAMEKEY_H

#include "player.h"


using namespace std;
//Uebernommen von Folien

class Game;
class GameKey{
	GameKey() {}	//Private. Moze implementirano bit i u GameKey.cpp
	friend bool Player::join_game(shared_ptr<Game>);
	friend bool Player::leave_game(shared_ptr<Game>);

};


#endif
