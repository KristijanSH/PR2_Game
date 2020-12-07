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
  bool Game::is_allowed(int n) const {    
    if( n*100 > host->get_mmr() * 90 && n*100 < host->get_mmr() * 110){ 
      return true;
    } else
      return false;
  }
bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p) ///unnötig kompliziert ? vielleicht nur .reset() od. release() ?
{
    if( players.count(p->get_name()) )
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
shared_ptr<Player>  Game :: best_player() const {
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

shared_ptr<Player> Game :: play (size_t i) {
/* auto winner = this->players.begin();
 
  for(size_t j = 0; j < i; j++)
    winner++;
 
 int winner_mmr = winner->second.get()->get_mmr();
  for(auto const& a: this->players) {
   if(winner->first == a.first) continue;
   if(a.second.get()->get_mmr() > winner_mmr) {
      a.second.get()->change_mmr(2*this->change(false)); 
   } else {
      a.second.get()->change_mmr(this->change(false));    
    }
  }  
  winner->second.get()->change_mmr(this->change(false));
  return winner->second;
*/  
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


ostream& Game::print(ostream&o) const
{
  bool first{true};
   o << "[" << name << ", " << host->get_name() << ", " << host->get_mmr() << ", player: {";


    for(const auto value: players)
    {
        if(first) first = false;
        else o << ", ";

        o << "[" << value.first << ", " << value.second->get_mmr() << "]";
    }
    o << "}]";
return o;
  
  } 

  ostream& RGame::print(ostream& o) const{  //Gibt das Objekt auf den ostream o aus; Format: Ranked Game: Game->Print
    o << "Ranked Game: ";
    return Game::print(o);
  }  


  ostream& UGame::print(ostream& o) const { //Gibt das Objekt auf den ostream o aus; Format: Game->Print
    o << "Unranked Game: ";
    return Game::print(o);
  }

  ostream& operator<<(ostream& o, const Game& g) {  //Global zu überladen;  bsp: [DotA 2, Juliane, 558, player: [Heinrich, 575], [Helmut, 582], [Juliane, 558]]
    return g.print(o);
  } 
  
