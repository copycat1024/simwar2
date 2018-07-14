#include <iostream>
#include <fstream>

#include "server.h"
#include "proxy.h"

using std::cout;
using std::ofstream;
using std::string;

namespace simwar {

	void Server::init(const string& hero_path){
		_dir.init(hero_path);
	}

	int Server::run_battle(const std::string& ta, const std::string& tb, SwLogStream& stream){
		Proxy proxy(_dir);
		LuaLogger log(stream, _dir);
		proxy.log = &log;
		return proxy.run_battle(ta, tb);
	}

	int Server::run_battle(const std::string& ta, const std::string& tb, const char* log_file){
		ofstream file;
		file.open(log_file);
		return run_battle(ta, tb, file);
	}

	int Server::run_battle(const std::string& ta, const std::string& tb){
		return run_battle(ta, tb, cout);
	}

	int Server::run_battle_nl(const std::string& ta, const std::string& tb){
		Proxy proxy(_dir);
		return proxy.run_battle(ta, tb);
	}
}
