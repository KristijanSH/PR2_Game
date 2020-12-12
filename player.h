#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<map>


using namespace std;

class Game;

enum class Mode{Ranked,Unranked, Mixed};

class Player:public enable_shared_from_this<Player>{	
	string name;
	int mmr;
	shared_ptr<Game> hosted_game;
	map<string, weak_ptr<Game>> games; 
public:
	Player(string name, int mmr) : name{name}, mmr{mmr} {
		if(name.size() == 0) {throw runtime_error("Empty name");}
		if(mmr < 0 || mmr > 9999) {throw runtime_error("MMR < 0 or > 9999!");}
	}
	string get_name() const {
		return name;
	}
	int get_mmr() const{
		return mmr;
	}
	shared_ptr<Game> get_hosted_game() const;
	void change_mmr(int n);
	bool host_game(string s, Mode m);
	bool join_game(shared_ptr<Game> g);
	bool leave_game(shared_ptr<Game> g);
	vector<weak_ptr<Player>> invite_players(const vector<weak_ptr<Player>>& v);
	bool close_game();
  ostream& print(ostream& o) const;	
};

	ostream& operator<<(ostream& o, const Player& p);	

	




#endif
