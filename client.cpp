#include <cstdlib>
#include "client.h"
#include "sol.hpp"

extern "C" {
#include <ncurses.h>
}

using std::string;
using std::to_string;


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

Client::Client(const char* filename){
	_file = string(filename);
	_hei = 3;
    _len = 10;
}

void Client::_frame(){
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

void Client::_line(int line, const char* data){
	int px, x;
    int y = 1+(_hei+1)*(_pos%3)+(line%_hei);
	if (_team%2==0){
		px = 2-_pos/3;
	} else {
		px = 4+_pos/3;
	}
	x = 1+(_len+1)*px;
    blit(x, y, data, _len);
}

void Client::_line(int line, string data){
	_line(line, data.c_str());
}

void Client::_line(int line, int data){
	_line(line, to_string(data));
}

void Client::_run_log(){
	sol::state lua;

	lua["pause"] = [this](){
		refresh();
		getch();
		while(!_seg.empty()){
			LineSeg ls = _seg.top();
			this->_team = ls.team;
			this->_pos = ls.pos;
			this->_line(ls.line, "");
			_seg.pop();
		}
	};
	lua["at"] = [this](int t, int p){
        this->_team = t;
        this->_pos = p;
	};
	lua["hp"] = [this](int hp){
		this->_line(1, hp);
	};
	lua["take"] = [this](int dmg){
		this->_line(0, dmg);
		_seg.push({this->_team, this->_pos, 0});
	};
	lua["focus"] = [this](int n){
		this->_line(0, n);
		_seg.push({this->_team, this->_pos, 0});
	};
	lua["name"] = [this](string name){
		this->_line(2, name);
	};
	lua.script_file(_file.c_str());
}

void Client::show(){
	initscr();
	_frame();
	_run_log();
	refresh();
	getch();
	endwin();
}
