#include <string>
#include <iostream>
#include <exception>

#include "team.h"
#include "entity.h"
#include "errors.h"

using std::string;
using std::cout;
using std::endl;

int base32(char c){
	if (c>='a' && c<='z') return c-'a';
	if (c>='A' && c<='Z') return c-'A';
	if (c>='2' && c<='7') return c-'2'+26;
	throw std::exception();
}

int factorial(int n){
	int res = 1;
	for (int i=1; i<n+1; i++){
		res *= i;
	}
	return res;
}

int combination(int n, int k){
	return factorial(n)/factorial(k)/factorial(n-k);
}

std::array<int, 5> intToFormation(int r){
	std::array<int, 5> res;
	const int k = 5;
	int i, p;
	for (i=k; i>0; i--){
		p = i;
		while (combination(p, i) < r)
			p++;
		r -= combination(p-1, i);
		res[i-1] = p-1;
	}
	return res;
}

simwar::TeamSetup stampToSetup(string stamp){
	simwar::TeamSetup res;

	// extract heroes data
	if (stamp.size()%5 != 2) throw std::exception();
	int hs = stamp.size()/5;
	for (int i=0; i<5; i++){
		int h = 0;
		int off = 2 + i*hs;
		for (int j=0; j<hs; j++){
			h *= 32;
			h += base32(stamp[off+j]);
		}
		res.heroes[i] = h;
	}

	// extract formation data
	int form = base32(stamp[0])*32 + base32(stamp[1]);
	if (form > 125) throw std::exception();
	res.formation = intToFormation(form+1); // start from 1

	return res;
}

namespace simwar{

	void Team::init(const string& stamp){

		// get team setup from stamp + check
		setup = stampToSetup(stamp);

		// load heroes' basic stats
		for (int i=0; i<5; i++){
			heroes[i][Key::ID]  = i;
			heroes[i][Key::HID] = setup.heroes[i];
			heroes[i][Key::Pos] = setup.formation[i];
		}

	}

	bool Team::isDead(int i) const{
		if (i>4 || i<0) return true;
		return heroes[i].at(Key::HP) <= 0;
	}

	bool Team::lost() const{
		for (int i=0; i<5; i++){
			if (!isDead(i)) return false;
		}
		return true;
	}

	void Team::nextHero(){
		do {
			active_hero++;
		} while (active_hero<5 && isDead(active_hero));
	}

	void Team::firstHero(){
		active_hero = -1;
	}
}
