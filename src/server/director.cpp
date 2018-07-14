#include <cstddef>
#include <dirent.h>
#include <iostream>
#include <string>
#include <vector>

#include "director.h"
#include "program.h"
#include "errors.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace simwar {

	Director::Director(){
		_init = false;
	}

	void Director::init(std::string hero_path){
		DIR *dirp;
		dirent *node;

		dirp = opendir(hero_path.c_str());
		if (dirp){
			while ((node = readdir(dirp)) != NULL){
				if (node->d_type == DT_REG){
					_hero_files.push_back(hero_path + string(node->d_name));
				}
			}
			closedir(dirp);
		} else {
			throw std::exception();
		}

		_hero_roles.resize(_hero_files.size());
		for (int i=0; i<_hero_files.size(); i++){
			_hero_roles[i].init(_hero_files[i]);
		}

		_load_info();
		_init = true;
	}

	const vector<string>& Director::hero_files() const{
		if (!_init) throw NotInitializeError();
		return _hero_files;
	}

	const vector<Role>& Director::hero_roles() const{
		if (!_init) throw NotInitializeError();
		return _hero_roles;
	}

	void Director::_load_info(){
		key_info[Key::HP] = string("hp");
		key_info[Key::AD] = string("ad");
		key_info[Key::HID] = string("hid");
		key_info[Key::ID] = string("id");
		key_info[Key::Pos] = string("pos");
		for (int i=0; i<_hero_roles.size(); i++){
			val_info[Key::HID][i] = _hero_roles[i].name();
		}
	}

}
