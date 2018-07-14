#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <exception>
#include <fstream>

#include "program.h"
//#include "client.h"
//#include "battle.h"
#include "program.h"
//#include "config.h"

using std::string;
using std::ofstream;

namespace simwar {
	
	Program::Program() {
		_init = false;
	}

	void Program::init(){

		// getting executable file path (Debian only)
		char buf[PATH_MAX + 1];
		ssize_t len = readlink("/proc/self/exe", buf, PATH_MAX);
		if (len < 0) exit(EXIT_FAILURE); // exit on failure, no throwing
		_path = string(buf);

		// getting executable folder path
		size_t last_slash = _path.find_last_of("/");
		_folder = _path.substr(0, last_slash + 1);

		_init = true;
	}

	const string& Program::path(){
		if (!_init) init();
		return _path;
	}

	const string& Program::folder(){
		if (!_init) init();
		return _folder;
	}
}
