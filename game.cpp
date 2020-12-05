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

	Game::Game(string name, shared_ptr<Player> host):name{name} {
		if(name.empty() || name.length() == 0) { throw new runtime_error("Name darf nicht leer sein!");}
		if(host == nullptr) {throw new runtime_error("Host darf nicht nullptr sein!");}
	}	
	string Game::get_name() const {
		return this->name;	//ili je return this->name; ? posto pise liefert den namen des this-objekts?
	}
	bool Game::is_allowed(int n) const {		// poseri mi se u usta ako ovo bude radilo
		//double hostMMR = host->mmr;
		//auto perc90 = mmr * 90 / 100;	//alt 1
		//auto perc110 = mmr * 110 / 100;	//alt 1
		if( n > host->get_mmr() * 0.90 || n < host->get_mmr() * 1.10){		//alt 1:	if(n > 90perc || n < 110perc)	//alt 2: sa float if( n > mmr * 9.0/10 || n < mmr * 11.0/10) 
			return true;
		} else
			return false;
	}
	bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p){
		bool checkDelete = false;
		if(p != nullptr) {
			p = nullptr;
			checkDelete = true;
		}
		if (checkDelete == true){
			return true;
		} else {
			return false;
		  }
		return checkDelete;  
    
    
    
    
		/*
bool Game::remove_player(const GameKey& gk, shared_ptr<Player> p){
    if(players.count(p->get_name())){//überprüft ob Player in Game
        players.erase(p->get_name());
        return true;
    }
    return false;
}
		*/
	}
/*	bool Game::add_player(const GameKey& gk, shared_ptr<Player> p) {
		if((Player::get_name() != p.get_name()) && ((p.get_mmr() < host.get_mmr() * 0.10 ) || (p.get_mmr() > host.get_mmr() * 0.10 ))) {
			players.insert({p->get_name(), p});
			return true;
		} else
			return false;
	}
*/
//	ne radi al mozda pomogne
bool Game :: add_player(const GameKey& gk, shared_ptr<Player> p)
{
    // von map alle namen durchzugehen und finden obs gleiche name gibt
    string pn = p->get_name();
    auto it = find_if (players.begin(), players.end(), [&pn](const pair <string, shared_ptr<Player>>& g)
        {     
            return pn == g.first;
        });
    if (it != players.end()) return false;

    if (is_allowed(p->get_mmr()))
    {
        players.emplace(p->get_name(), p);
        return true;
    }
}
shared_ptr<Player>  Game :: best_player() const

{
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
	shared_ptr<Player> Game::play(size_t i){
		shared_ptr<Player> winner;
		for(auto it : players) {
			auto mmr =  it.second->get_mmr();
      size_t it_mmr  = it.second->get_mmr();
			if(it_mmr != i && it_mmr < mmr) {
				mmr = 1*change(false);
			}
			if(it_mmr != i && it_mmr >  mmr) {
				mmr = 2*change(false);
			}
			if (it.second->get_mmr() == i) {
				mmr = change(true);
        //this->hosted_game = make_shared<RGame>(s, shared_from_this());
				winner = make_shared<Player>();
			}
		}
		return winner;
	}
//	virtual int change(bool) const() = 0;
//	virtual ~Game(){ // = default;
//		delete[] players;
//  }  
    
	/*virtual*/ ostream& Game::print(ostream& o) const {	//[name, host->name,host->mmr]   || {[Player_name,Player_mmr], [Player_name,Player_mmr],...}
		o << '[' << name << ", " << host->get_name() << ", " << host->get_mmr() << ", player: {";
		bool first = true;
		for(auto it = this->players.begin(); it != this->players.end(); ++it) {
			if (first)
				first = false;
			else
				o << ", ";
			o << '[' << it->second->get_name() << ", " << it ->second->get_mmr() << "], ";
		}
		o << "}]";
		return o;
	} 

	//TODO:
	ostream& operator<<(ostream& o, const Game& g) {	//Global zu überladen;	bsp: [DotA 2, Juliane, 558, player: [Heinrich, 575], [Helmut, 582], [Juliane, 558]]
		return g.print(o);
	}	
	//Hinweis: Um shared_pointer vom this-Objekt zu erzeugen, muss die Klasse Game public von enable_shared_from_this<Game> erben!

	//ovdje vjerojatno ne valja output, al barem nema errora
	ostream& RGame::print(ostream& o) const{	//Gibt das Objekt auf den ostream o aus; Format: Ranked Game: Game->Print
		Game::print(o);
    o << "Ranked Game: " << get_name();
    return o;
  }  


 	ostream& UGame::print(ostream& o) const {	//Gibt das Objekt auf den ostream o aus; Format: Game->Print
		Game::print(o);
    o << "Ranked Game: " << get_name();
    return o;
  }
  
