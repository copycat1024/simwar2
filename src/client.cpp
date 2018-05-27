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
	_hei = 3;
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

void ClientWrap::_line(int team, int pos, int line, string data){
	_line(team, pos, line, data.c_str());
}

void ClientWrap::_line(int team, int pos, int line, int data){
	_line(team, pos, line, to_string(data));
}

void ClientWrap::_pause(){
	refresh();
	getch();
}

SwClient::SwClient(const char* filename): _file(filename){
}

void SwClient::_run_log(){
	sol::state lua;
	lua["init_start"] = [this](){};
	lua["init_hero"] = [this](int id){
		cout << id << endl;
//		this->_line(id/5, pos, 2, name);
	};
	lua["init_end"] = [this](){
		this->_pause();
	};
	lua.script_file(_file.c_str());
}

void SwClient::show(){
	cout << "show" << endl;
	initscr();
	_frame();
	_run_log();
	_pause();
	endwin();
}
