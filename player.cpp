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

  shared_ptr<Game> Player::get_hosted_game() const {
    return this->hosted_game;
  }

  void Player::change_mmr(int n){
    if(mmr > 0 || mmr < 9999) 
      mmr += n;
  }

 bool Player::host_game(std::string s, Mode m) {
        if(s.empty()) throw std::runtime_error{"empty string"};
        if(this->hosted_game == nullptr){
        switch (m){
            case Mode::Ranked:
                hosted_game = std::make_shared<RGame>(s, shared_from_this());
                return true;

            case Mode::Unranked:
                hosted_game = std::make_shared<UGame>(s, shared_from_this());
                return true;
                
            case Mode::Mixed:
                hosted_game = std::make_shared<MGame>(s, shared_from_this());
                return true;
                }
        } return false; 
 }


bool Player::join_game(std::shared_ptr<Game> g) {
  GameKey gamekey;
  
  if(g->add_player(gamekey,shared_from_this())){
    const auto [it, success] = games.insert_or_assign(g->get_name(), g);
    if (!success && (*it).second.expired()){
      games.at(g->get_name()) = g;
      return true;
    }
    return success;
  }
  return false;
}


  bool Player::leave_game(shared_ptr<Game> g) {
    GameKey gamekey; 
    bool removed = false;
    
    if(g->remove_player(gamekey, shared_from_this()) && this->games.erase({g->get_name()})){
    
      removed = true;
    }
    
   if(removed)
     return true;
   else
     return false;
  }


  vector<weak_ptr<Player>> Player::invite_players(const vector<weak_ptr<Player>>& v) {
    vector<weak_ptr<Player>> inviteListe;
    
     for(auto& elem : v) {
        bool isOK = false;
         if(elem.expired()) isOK = true;
           else {
           shared_ptr<Player> tmp = elem.lock();
             if(tmp->join_game(this->get_hosted_game())) {}
             else
                 isOK = true;      
           }  
           if(isOK)
             inviteListe.push_back(elem);
        }  
    return inviteListe;
  }



bool Player::close_game(){
    if(get_hosted_game()!=nullptr) {
      hosted_game = nullptr;
        return true;}
    return false;}


  ostream& Player::print(ostream& o) const{ //Format: [name, mmr, hosts: hosted_game_name, games: {Game_name, Game_game, ...}]
    o << '[' << name << ", " << this->get_mmr() << ", " << "hosts: " ; 
    if(hosted_game == nullptr)
      o << "nothing";
    else
      o << hosted_game->get_name();
    o << ", games: {";
    
    bool first = true;
    for(const auto& a : games) {
     if(!a.second.expired()) {
      if (first) {
       o << a.first;
        first = false;
      }
       else {
          o << ", " << a.first; 
       }
     }
      
    }  
    o << "}]";
    return o;
  
  }
  
  ostream& operator<<(ostream& o, const Player& p) {  
    return p.print(o);
  }

