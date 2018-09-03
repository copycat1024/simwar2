#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <exception>
#include <fstream>
#include <string>
#include <vector>

#include "program.h"

using std::string;
using std::exception;
using std::ofstream;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

namespace simwar {

	const char* Program::_default_log_file = "log.lua";

	Program::Program() {
		_init = false;
	}

	void Program::init(){
		_init_path();
		_init_server();
		_init = true;
	}

	void Program::_init_path(){
		// getting executable file path (Debian only)
		char buf[PATH_MAX + 1];
		ssize_t len = readlink("/proc/self/exe", buf, PATH_MAX);
		if (len < 0) exit(EXIT_FAILURE); // exit on failure, no throwing
		_path = string(buf);

		// getting executable folder path
		size_t last_slash = _path.find_last_of("/");
		_folder = _path.substr(0, last_slash + 1);
	}

	void Program::_init_server(){
		string hero_path = _folder + "lua/default/hero/";
		_server.init(hero_path);
	}

	const string& Program::path(){
		if (!_init) init();
		return _path;
	}

	const string& Program::folder(){
		if (!_init) init();
		return _folder;
	}

	void Program::execute(int argc, char** argv){

		// populate args
		vector<string> args;
		for (int i=0; i<argc; i++) args.push_back(string(argv[i]));

		if (args.size() > 1){
			if (args[1] == "battle"){
				if (args.size() == 5){
					battleToFile(args[2], args[3], args[4]);
					return;
				}
				if (args.size() == 4){
					battleToFile(args[2], args[3], _default_log_file);
					return;
				}
			}
			if (args[1] == "client"){
				if (args.size() == 3){
					clientFromFile(args[2]);
					return;
				}
				if (args.size() == 2){
					clientFromFile(_default_log_file);
					return;
				}
			}
		}

		_printHelp(args[0]);

	}

	int Program::battleToFile(const std::string& team_a, const std::string& team_b, const std::string& log_file){
		int res;
		try {
			res = _server.run_battle(team_a, team_b, log_file.c_str());
		} catch (exception& e){
			cerr << "Error: "<< e.what() << endl;
			return -1;
		}
		return res;
	}

	void Program::clientFromFile(const std::string& log_file){
		try {
			_client.run(log_file.c_str());
		} catch (exception& e){
			cerr << "Error: "<< e.what() << endl;
		}
	}

	void Program::_printHelp(const string& exec_name){
		cout << "Usage:" << endl;
		cout << endl;
		cout << exec_name << " battle <team_a> <team_b> <log_file>" << endl;
		cout << "  Run battle, write log to log_file." << endl;
		cout << endl;
		cout << exec_name << " battle <team_a> <team_b>" << endl;
		cout << "  Run battle, write log to " << _default_log_file << "." << endl;
		cout << endl;
		cout << exec_name << " client <log_file>" << endl;
		cout << "  Run client, read log from log_file." << endl;
		cout << endl;
		cout << exec_name << " client" << endl;
		cout << "  Run client, read log from " << _default_log_file << "." << endl;
		cout << endl;
	}

}
