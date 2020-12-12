#ifndef GAME_H
#define GAME_H

#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<map>
#include "player.h"
#include "gamekey.h"

using namespace std;

class Game:public enable_shared_from_this<Game>{
string name;
shared_ptr<Player> host;
map<string, shared_ptr<Player>> players;

public:
	Game(string name, shared_ptr<Player> host);	
	string get_name() const;
	bool is_allowed(int n) const;
	bool remove_player(const GameKey& gk, shared_ptr<Player> p);
	bool add_player(const GameKey& gk, shared_ptr<Player> p);
	shared_ptr<Player> best_player() const;
	size_t number_of_players() const;
	shared_ptr<Player> play(size_t i);
	virtual int change(bool) const = 0;
	virtual ~Game() = default;
  virtual bool testi_test() const;
  shared_ptr<Player> get_host() const;
  
	virtual ostream& print(ostream& o) const; 
};
	
class RGame:public Game{
public:
	RGame(string name, shared_ptr<Player> host):Game(name, host){} 
	int change(bool x) const override {		
		if(x == true) return 5;
			else return -5;
	}
  bool testi_test() const override;
	ostream& print(ostream& o) const override;	
};

class UGame:public Game {
public:
	UGame(string name, shared_ptr<Player> host):Game(name, host){} 
	int change(bool) const override {
		return 0;
	}
  bool testi_test() const override;
 	ostream& print(ostream& o) const override;	
};

class MGame:public Game {
  static int punkte;
  public:
  	MGame(string, shared_ptr<Player>);
  	static void increase_counter();
  	int change (bool) const;
  	ostream& print(ostream& o) const;
};


ostream& operator<<(ostream& o, const Game& g);
#endif
