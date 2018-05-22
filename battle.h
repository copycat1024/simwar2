#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <vector>
#include <array>
#include "hero.h"

typedef std::vector<std::string> Log;

class Battle{
public:
	// Main interface
	Battle();
	void run();
	bool over();
	Log& get_log();

private:
	// Hero interface
	friend Hero;
	static const int _hero_num = 10;
	std::array<std::string, _hero_num> _hero_name;
	std::array<Hero*, _hero_num> _heros;
	std::array<int, _hero_num> _hero_pos;
	sol::table _map(int);
	void _invoke(int src, int tar, std::string state_name, int delta);

	// Log interface
	Log _log;
	void _write_log(std::string, int);
};

#endif
