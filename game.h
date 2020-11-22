#ifndef GAME_H
#define GAME_H

#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<map>



class Game{
string name;
shared_ptr<Player> host;
map<string, shared_ptr<Player>> players;

public:
	Game(string name, shared_ptr<Player> host);
	string get_name() const;
	bool is_allowed(int n) const;
	bool remove_player(const GameKey$ gk, shared_ptr<Player> p);
	

}


#endif
