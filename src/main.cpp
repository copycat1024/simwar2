#include <fstream>
#include <iostream>
#include <cstring>
#include "client.h"
#include "battle.h"
#include "config.h"

using std::ofstream;
using std::cout;
using std::endl;

void run_battle(const char*, const char*, const char*);
void run_client(const char*);
void print_help(const char*);

int main(int argc, char** argv){
	const char* default_log_file = "battle_log.lua";

	if (argc < 2){
		print_help(argv[0]);
	} else if (strcmp(argv[1], "battle") == 0){
		if (argc == 2){
			run_battle(default_log_file, DEFAULT_TEAM_A_PATH, DEFAULT_TEAM_B_PATH);
		} else if (argc == 3){
			run_battle(argv[2], DEFAULT_TEAM_A_PATH, DEFAULT_TEAM_B_PATH);
		} else if (argc == 4){
			run_battle(default_log_file, argv[2], argv[3]);
		} else if (argc == 5){
			run_battle(argv[2], argv[3], argv[4]);
		} else {
			print_help(argv[0]);
		}
	} else if (strcmp(argv[1], "client") == 0){
		if (argc == 2){
			run_client(default_log_file);
		} else if (argc == 3){
			run_client(argv[2]);			
		} else {
			print_help(argv[0]);
		}
	} else {
		print_help(argv[0]);
	}
}

void run_battle(const char* log_file, const char* team_a, const char* team_b){
	ofstream file;
	file.open(log_file);
	SwBattle b(file, DEFAULT_HERO_PATH, team_a, team_b);
	b.run();
	cout << b.winner << endl;
}

void run_client(char const* log_file){
	SwClient c(log_file, CLIENT_LUA_PATH);
	c.show();
}

void print_help(const char* exe_path){
	cout << "Usage:" << endl;
	cout << exe_path << " battle" << endl;
	cout << exe_path << " battle <log_file>" << endl;
	cout << exe_path << " battle <team_a_file> <team_b_file>" << endl;
	cout << exe_path << " battle <log_file> <team_a_file> <team_b_file>" << endl;
	cout << exe_path << " client" << endl;
	cout << exe_path << " client <log_file>" << endl;
}
