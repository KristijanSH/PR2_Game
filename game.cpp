#include "game.h"
#include "player.h"
#include "gamekey.h"
#include<string>
#include<iostream>
#include<algorithm>
#include<memory>
#include<numeric>
#include<vector>
#include<map>

using namespace std;

  Game::Game(string name, shared_ptr<Player> host):name{name}, host{host} {
    if(name.empty() || name.length() == 0) { throw new runtime_error("Name darf nicht leer sein!");}
    if(host == nullptr) {throw new runtime_error("Host darf nicht nullptr sein!");}
  } 
  string Game::get_name() const {
    return this->name;
  }
	shared_ptr<Player> Game::get_host() const {
 		return host; 
	}
  bool Game::is_allowed(int n) const {    
    if( n*100 > host->get_mmr() * 90 && n*100 < host->get_mmr() * 110){ 
      return true;
    } else
      return false;
  }
bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p) {
    if(players.count(p->get_name()))
    {
        players.erase(p->get_name());
        return true;
    }
    else return false;
}


bool Game::add_player(const GameKey& gk, shared_ptr<Player> p) {
  if(is_allowed(p->get_mmr())) {
      this->players.insert({p.get()->get_name(), p});
    
      return true;
    }
  
auto fPlayer = players.find(p->get_name());
    if(fPlayer != this->players.end()) { return false;}
  
  return false;
}


shared_ptr<Player>  Game::best_player() const {
  if (players.empty()) throw runtime_error("");
  auto a = max_element (players.begin(), players.end(), [] (const pair <string, shared_ptr<Player>>& g, const pair <string, shared_ptr<Player>>& g1) {
    return g.second->get_mmr() < g1.second->get_mmr();
  });
    auto p = a->second;
  return p;
}

size_t Game::number_of_players() const{
    return players.size();
  }

shared_ptr<Player> Game::play (size_t i) {
  shared_ptr<Player> winner = (next(players.begin(), i)->second);
  for(const auto& p : players) {
    if(winner != p.second) {
      if(p.second->get_mmr() <= winner->get_mmr()) p.second->change_mmr(change(false));
      else
        p.second->change_mmr(change(false)*2);
    }
  }  
    winner->change_mmr(change(true));
    return winner;
}

	bool Game::testi_test() const {
   	return false; 
  } 

ostream& Game::print(ostream&o) const {
  bool first{true};
  
   o << "[" << name << ", " << host->get_name() << ", " << host->get_mmr() << ", player: {";
    for(const auto value: players) {
        if(first) first = false;
        else o << ", ";

        o << "[" << value.first << ", " << value.second->get_mmr() << "]";
    }
      o << "}]";
      return o;
} 

  ostream& RGame::print(ostream& o) const { 
    o << "Ranked Game: ";
    return Game::print(o);
  }  
	
	bool RGame::testi_test() const {
   	if(get_host()->get_mmr() % 2 == 0)
      return true;
    else
      return false;
  } 


  ostream& UGame::print(ostream& o) const { 
    o << "Unranked Game: ";
    return Game::print(o);
  }

	bool UGame::testi_test() const {
   	if(get_host()->get_mmr() % 2 == 0)
      return true;
    else
      return false;
  } 

//  --- aufgabe 3
	int MGame::punkte = 0;
	MGame::MGame(string s, shared_ptr<Player> p) : Game::Game(s,p) {}
	void MGame::increase_counter() {
 	if(punkte + 1 > 10) punkte = 0;
	  else ++punkte;
	}
	int MGame::change(bool) const {
    return punkte;
  }
	ostream& MGame::print(ostream& o) const {
   o<<"Mixed Game: ";
    return Game::print(o);
  }  




  ostream& operator<<(ostream& o, const Game& g) {
    return g.print(o);
  } 
  
