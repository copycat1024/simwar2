#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <array>
#include "hero.h"

enum class SwClientLine:int{
	Symbol = 0,
	Name = 1,
	HP = 2,
	AD = 3,
	Debug = 4,
};

// ncurses wrapper for SwClient
class ClientWrap{
protected:
	ClientWrap();
    int _len, _hei;
	void _frame();
	void _line(int, int, int, const char*);
	void _line(int, int, int, std::string);
	void _line(int, int, int, int);
	void _pause();
};

class SwClient;
class SwClientHero:public SwHero{
	friend SwClient;
	void show(SwClient&);
	void alter(SwHeroKey, EntityValue);
	std::string name;
	EntityValue _delta;
};

class SwClient:ClientWrap{
public:
	SwClient(const char* filename, const char* luapath);
	~SwClient();
    void show();
private:
	friend SwClientHero;
	static const int _hero_num = 10;
	std::array<SwClientHero*, _hero_num> _heros;

	void _line(int, SwClientLine, const char*);
	void _line(int, SwClientLine, std::string);
	void _line(int, SwClientLine, int);

	void _refresh();

	void _run_log();
    int _team, _pos;
    int _turn;
	std::string _file;

	const char* _lua_path;
};

#endif
