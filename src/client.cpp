#include <cstdlib>
#include <iostream>
#include "client.h"
#include "sol.hpp"

extern "C" {
#include <ncurses.h>
}

using std::string;
using std::to_string;
using std::cout;
using std::endl;

void blit(int x, int y, const char* s, int l){
    int i=0;
	while (i<l && s[i]){
		mvaddch(y, x+i, s[i]);
		i++;
	}
	while (i<l){
		mvaddch(y, x+i, ' ');
        i++;
	}
	move(0, 0);
}

ClientWrap::ClientWrap(){
	_hei = 5;
    _len = 10;
}

void ClientWrap::_frame(){
	int i,j;
	for (i=0; i<(_hei+1)*4; i+=_hei+1){
		for (j=0; j<(_len+1)*8; j+=_len+1){
			mvaddch(i, j, '+');
		}
	}
	for (i=0; i<(_hei+1)*3; i++){
		for (j=0; j<(_len+1)*8; j+=_len+1){
			if (i%(_hei+1)!=0) mvaddch(i, j, '|');
		}
	}
	for (i=0; i<(_hei+1)*4; i+=_hei+1){
		for (j=0; j<(_len+1)*7; j++){
			if (j%(_len+1)!=0 && j/(_len+1)!=3) mvaddch(i, j, '-');
		}
	}
}

void ClientWrap::_line(int team, int pos, int line, const char* data){
	int px, x;
    int y = 1+(_hei+1)*(pos%3)+(line%_hei);
	if (team%2==0){
		px = 2-pos/3;
	} else {
		px = 4+pos/3;
	}
	x = 1+(_len+1)*px;
    blit(x, y, data, _len);
}

inline void ClientWrap::_line(int team, int pos, int line, string data){
	_line(team, pos, line, data.c_str());
}

inline void ClientWrap::_line(int team, int pos, int line, int data){
	_line(team, pos, line, to_string(data));
}

void ClientWrap::_pause(){
	refresh();
	getch();
}

void SwClientHero::alter(SwHeroKey k, EntityValue v){
    SwHero::alter(k, v);
	_delta = v;
}

void SwClientHero::show(SwClient& c){
	if (id() == c._turn){
		c._line(id(), SwClientLine::Symbol, "***");
	} else if (_delta!=0) {
		c._line(id(), SwClientLine::Symbol, _delta);
		_delta = 0;
	} else {
		c._line(id(), SwClientLine::Symbol, "");
	}
	if (isDead()){
		c._line(id(), SwClientLine::Name, "_");
		c._line(id(), SwClientLine::HP, "x");
	} else {
		c._line(id(), SwClientLine::Name, name);
		c._line(id(), SwClientLine::HP, hp());
	}
//	c._line(this->id(), SwClientLine::Debug, (*this)[SwHeroKey::DB]);
}

SwClient::SwClient(const char* filename, const char* luapath): _file(filename), _lua_path(luapath){
}

SwClient::~SwClient(){
	for (auto h: _heros){
		delete h;
	}
}

inline void SwClient::_line(int id, SwClientLine line, const char* data){
	ClientWrap::_line(id/5, (*_heros[id])[SwHeroKey::PS], (int)line, data);
}

inline void SwClient::_line(int id, SwClientLine line, string data){
	ClientWrap::_line(id/5, (*_heros[id])[SwHeroKey::PS], (int)line, data);
}

inline void SwClient::_line(int id, SwClientLine line, int data){
	ClientWrap::_line(id/5, (*_heros[id])[SwHeroKey::PS], (int)line, data);
}

void SwClient::_refresh(){
	for (auto h: _heros){
		h->show(*this);
	}
	_pause();
}

void SwClient::_run_log(){
	sol::state lua;
	_turn = -1;
	lua.open_libraries(sol::lib::base);
	lua["echo"] = [](string txt){
//		cout << txt << endl;
	};
	lua.script_file(_lua_path);
	lua["turn_start"] = [this](int id){
		this->_turn = id;
		this->_refresh();
	};
	lua["init_hero"] = [this](EntityValue id, string name, EntityValue pos){
		_heros[id] = new SwClientHero();
		_heros[id]->name = name;
		(*this->_heros[id])[SwHeroKey::ID] = id;
		(*this->_heros[id])[SwHeroKey::PS] = pos;
	};
	lua["init_end"] = [this](){
		for (auto h: _heros){
			h->_delta = 0;
		}
		this->_refresh();
	};
	lua["turn_end"] = [this](){
		this->_refresh();
	};
	lua["alter"] = [this](int id, SwHeroKey key, EntityValue delta){
		this->_heros[id]->alter(key, delta);
	};
	lua.script_file(_file.c_str());
}

void SwClient::show(){
	initscr();
	_frame();
	_run_log();
	_pause();
	endwin();
}
