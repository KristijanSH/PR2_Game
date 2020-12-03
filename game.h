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
	Game(string name, shared_ptr<Player> host);	//TODO: Konstruktor
	string get_name() const;
	bool is_allowed(int n) const;
	bool remove_player(const GameKey& gk, shared_ptr<Player> p);
	bool add_player(const GameKey& gk, shared_ptr<Player> p);
	shared_ptr<Player> best_player() const;
	size_t number_of_players() const;
	shared_ptr<Player> play(size_t i);
	virtual int change(bool) const = 0;
	virtual ~Game() = default;

	virtual ostream& print(ostream& o) const; //[name, host->name,host->mmr]   || {[Player_name,Player_mmr], [Player_name,Player_mmr],...}

	//TODO:
	//operator<<();	//Global zu überladen;	bsp: [DotA 2, Juliane, 558, player: [Heinrich, 575], [Helmut, 582], [Juliane, 558]]

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

#endif
