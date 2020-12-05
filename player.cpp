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
/*		string tmpName = g->get_name();
		auto it = games.find(tmpName);
		if(it == games.end()) {
			games.insert({tmpName, g});
			Game emag;
			emag.add_player(const GameKey& gk, shared_ptr<Player> p);	//valjda?
			return true;
		}
		return false;
*/    
  /*
  auto findP = find_if(g->get_players().begin(), g->get_players().end(), [&thisname](const pair<string, shared_ptr<Player>>& val) {
        return val.second->get_name() == thisname;
    });
if (findP != g->get_players().end()) return false;
  */
    
	}
	bool Player::leave_game(shared_ptr<Game> g) {
    // g aus der map loeschen, und auch this aus g.players loeschen
    //remove_if bei games und dann bei players
    string gn = g->get_name();
    auto res = remove_if(games.begin(), games.end(), [&gn](const pair <string, weak_ptr<Game>>& ga)
        {
            return gn == ga.first;
        });

    if (res == games.end()) return false;
    games.erase(res, games.end());
    auto p = shared_from_this();
    GameKey gk;
    bool pl = g->remove_player(gk, p);
    
    if (pl) return true;
    
    return false;

	}

	vector<weak_ptr<Player>> Player::invite_players(const vector<weak_ptr<Player>>& v) {
		vector<weak_ptr<Player>> inviteListe;

		for(auto const& nesto : v) {
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
		bool first = false;
    o << '[' << name << ", " << mmr << ", " << "hosts: " << hosted_game->get_name() << "games: {";
	
		for(auto& elem : games) {
			if (first) o << ", ";
			else
        first = true;
				o << elem.second.lock()->get_name();
    }  
		o << "}]";
			return o;
	}
	
	ostream& operator<<(ostream& o, const Player& p) {	//If hosted_game.empty() soll "nothing" ausgegeben werden. Bsp: [Heinrich, 20, hosts: nothing, games{Sims 4, Sims3, Doom}]
//	if(hosted_game == nullptr) o << "nothing \n";
    return p.print(o);
  }

