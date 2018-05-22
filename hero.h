#ifndef HERO_H
#define HERO_H

#include <string>
#include "sol.hpp"

class Battle;

class Hero{
public:
	Hero(Battle* bat, int id);
	void turn();
	bool isDead();
private:
	friend Battle;
	Hero();
	void _load_api();
	sol::state _lua;
	Battle* _bat;
	int _id;
};

#endif
