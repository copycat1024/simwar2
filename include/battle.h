#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <vector>
#include <array>
#include <ostream>
#include "hero.h"

typedef std::ostream SwLogStream;

class SwBattle{
public:

	// Main interface
	SwBattle(SwLogStream&, const char*);
	~SwBattle();
	void run();
	bool over();

	// Log interface
	SwLogStream& log;

private:

	// Hero manager
	friend SwBattleHero;
	static const int _hero_num = 10;
	const char* _hero_path;
	std::array<std::string, _hero_num> _hero_name;
	std::array<SwBattleHero*, _hero_num> _heros;
	std::array<int, _hero_num> _hero_pos;
};

#endif
