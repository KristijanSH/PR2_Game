#include "player.h"
#include "game.h"
#include "gamekey.h"
#include<string>
#include<iostream>
#include<memory>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

class Game;

//enum class Mode{Ranked,Unranked};


//	string name;
//	int mmr;
//	shared_ptr<Game> hosted_game;
//	map<string, weak_ptr<Game>> games; //Map von Spielen an denen Player teilnimmt
//public:
//	Player(string name, int mmr): name{name}, mmr{mmr} {};
//	string get_name() const;
//	int get_mmr() const;
	shared_ptr<Game> Player::get_hosted_game() const{
		return this->hosted_game;
	}
	void Player::change_mmr(int n){
		if(mmr > 0 || mmr < 9999) 
			mmr += n;
	}
	bool Player::host_game(string s, Mode m) {
		if(s.empty()) throw new runtime_error("empty string!");
		if(hosted_game) return false;
		
		if(m == Mode::Ranked) {
			this->hosted_game = make_shared<RGame>(s, shared_from_this());
		} else if(m == Mode::Unranked) {
			this->hosted_game = make_shared<UGame>(s, shared_from_this());
		}	
		return true;
	}
	/*
bool Player::host_game(string s, Mode m)
{
    
    if (s.empty()) throw runtime_error("empty name");
    if (hosted_game == nullptr)
    {
        
        //shared_ptr<Player> p{ make_shared<Player>(this) };
    
        if (m == Mode::Ranked)
        {
            RGame rg(s, shared_from_this());
            hosted_game = make_shared<RGame>(rg);
        }
        else
        {
            UGame rg(s, shared_from_this());
            hosted_game = make_shared<UGame>(rg);
        }
        return true;
        }
    else return false;
     

}
	*/

//	HOST_GAME V2
/*
bool Player::host_game(string s, Mode m)
{
  if (s.empty()) throw runtime_error("empty name");
	if(this->hosted_game == nullptr) {
  	switch (m) {
    	case Mode::Ranked:
      	hosted_game = make_shared<RGame>(s, shared_from_this());
        return true;
        
      case Mode::Unranked:
      	hosted_game = make_shared<UGame>(s, shared_from_this());
        return true;
    }
  }
  return false;
}
*/
	bool Player::join_game(shared_ptr<Game> g) {
		string tmpName = g->get.name();
		auto it = games.find(tmpName);
		if(it == games.end()) {
			games.insert({tmpName, g});
			Game emag;
			emag.add_player(const GameKey& gk, shared_ptr<Player> p);	//valjda?
			return true;
		}
		return false;
	}
	bool Player::leave_game(shared_ptr<Game> g) {
		string currentG = g.get_name();
		if(games.find(currentG)) {
			games.erase(currentG);
			delete this->g;
			return true;
		} else
			return false;

	}
	vector<weak_ptr<Player>> Player::invite_players(const vector<weak_ptr<Player>>& v) {
		vector<weak_ptr<Player>> inviteListe;

		for(auto cont& nesto : v) {
			bool isok = false;
			if(nesto.lock() && this->get_hosted_game().get()) {
				if(nesto.lock()->join_game(this->get_hosted_game())) {
					isok = true;
					this->games.insert({this->get_name(), this->get_hosted_game()});
				}
			}
		if(!nesto.lock() || !isok)
			inviteListe.push_back(nesto);	
		}

		return inviteListe;
	}
	bool Player::close_game(){

		hosted_game.reset();

	}


	ostream& Player::print(ostream& o) const{	//Format: [name, mmr, hosts: hosted_game_name, games: {Game_name, Game_game, ...}]
	o << '[' << name << ", " << mmr << ", " << "hosts: " << hosted_game.get_name();
	bool first = true;
	for(auto it = this->players.begin(); it != this->players.end(), it++) {
		if (first)
			first = false;
		else
			o << ":";
		o << '{' << it->first << "} ";
	}
		o << ']';
		return o;
	}
	
	operator<<;	//If hosted_game.empty() soll "nothing" ausgegeben werden. Bsp: [Heinrich, 20, hosts: nothing, games{Sims 4, Sims3, Doom}]

	

