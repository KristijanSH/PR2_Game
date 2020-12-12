#ifndef TASKS_H
#define TASKS_H
#include<iostream>
#include<memory>
#include<vector>
#include<experimental/iterator>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include "game.h"
#include "player.h"
#include "gamekey.h"


using namespace std;


string get_longest_name(const vector<weak_ptr<Player>>& v){
  if(v.empty()) throw runtime_error("v ist empty!");
  bool exp{true};
  vector<weak_ptr<Player>> cpy;
  
  for(const auto& a : v)
    if(!a.expired()) {
     	exp = false;
      cpy.push_back(a);
    }  
  if(exp) throw runtime_error("weak ptr expired");
  
  auto it = *max_element(cpy.begin(), cpy.end(), [](auto& lop, auto& rop) {
  	return lop.lock()->get_name().size() < rop.lock()->get_name().size();
  });
  
  return it.lock()->get_name();
}







#endif
