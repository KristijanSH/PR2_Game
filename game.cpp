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

class Game:public enable_shared_from_this<Game>{
string name;
shared_ptr<Player> host;
map<string, shared_ptr<Player>> players;

public:
	Game::Game(string name, shared_ptr<Player> host):name{name},{
		if(name.empty() || name.length() == 0) { throw new runtime_error("Name darf nicht leer sein!");}
		if(host == nullptr) {throw new runtime_error("Host darf nicht nullptr sein!");}
	}	
	string get_name() const {
		return name;	//ili je return this->name; ? posto pise liefert den namen des this-objekts?
	}
	bool Game::is_allowed(int n) const {		// poseri mi se u usta ako ovo bude radilo
		//double hostMMR = host->mmr;
		auto 90perc = mmr * 90 / 100;	//alt 1
		auto 110perc = mmr * 110 / 100;	//alt 1
		if( n > mmr * 0.90 || n < mmr * 1.10){		//alt 1:	if(n > 90perc || n < 110perc)	//alt 2: sa float if( n > mmr * 9.0/10 || n < mmr * 11.0/10) 
			return true;
		} else
			return false;
	}
	bool Game::remove_player(const GameKey$ gk, shared_ptr<Player> p){
		bool checkDelete = false;
		if(p != nullptr) {
			delete p;
			checkDelete = true;
		}
		if (checkDelete == true){
			return true;
		} else {
			return false;
		  }
		return checkDelete;  
	}
	bool Game::add_player(const GameKey& gk, shared_ptr<Player> p) {
		if((Player::get_name() != p.get_name()) && ((p.get_mmr() < host.get_mmr() * 0.10 ) || (p.get_mmr() > host.get_mmr() * 0.10 ))) {
			players.insert({p->get_name(), p});
			return true;
		} else
			return false;
	}

	shared_ptr<Player> best_player() const{
		shared_ptr<Player> mwp;
		if(players.empty()) throw new runtime_error("Players empty!");
		else {
			mwp = *max_element(players.begin(), players.end(), [=](auto p1, auto p2) {
				return p1.get_mmr() < p2.get_mmr();
			});
		
		return mwp;
		}
		if(players.count() > 1)
			return players.first;
	}						
	size_t number_of_players() const{
	size_t PlayerCounter = 0;
    for(auto i : players){
        if(!i.second.expired()){
            PlayerCounter++;
        }
    }
    return PlayerCounter;
	}
	shared_ptr<Player> play(size_t i);	//TODO
	virtual int change(bool) const = 0;
	virtual ~Game() = default;

	virtual ostream& print(ostream& o) const; //[name, host->name,host->mmr]   || {[Player_name,Player_mmr], [Player_name,Player_mmr],...}

	//TODO:
	operator<<();	//Global zu überladen;	bsp: [DotA 2, Juliane, 558, player: [Heinrich, 575], [Helmut, 582], [Juliane, 558]]

	//Hinweis: Um shared_pointer vom this-Objekt zu erzeugen, muss die Klasse Game public von enable_shared_from_this<Game> erben!

};

class RGame:public Game{
public:
	RGame(string, shared_ptr<Player>); //setzt Instanzvariablen durch Konstruktor des Basisklasse
	int change(bool x) const {		// Liedert 5 falls x true ist, ansonsten -5
		if(x == true) return 5;
			else return -5;
	}
	ostream& print(ostream o) const;	//Gibt das Objekt auf den ostream o aus; Format: Ranked Game: Game->Print
};

class UGame:public Game {
public:
	UGame(string, shared_ptr<Player>); //Setzt instanzvariablen durch Konstruktor der Basisklasse
	int change(bool) const {
		return 0;
	}
 	ostream& print(ostream& o) const;	//Gibt das Objekt auf den ostream o aus; Format: Game->Print
};
