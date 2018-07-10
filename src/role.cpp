#include <iostream>
#include <string>
#include <exception>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "role.h"
#include "errors.h"

using std::cout;
using std::endl;
using std::string;

namespace simwar {

	Role::Role(){
		_init = false;
		_L = 0;
	}

	Role::~Role(){
		if (_L){
			lua_close(_L);
		}
	}

	void Role::init(std::string file_name){
		// getting hero name
		size_t last_slash = file_name.find_last_of("/");
		_name = file_name.substr(last_slash + 1, file_name.size() - last_slash - 5);

		// load lua code
		_L = luaL_newstate();
		if (luaL_loadfile(_L, file_name.c_str())){
			_L = 0;
		}
		if (lua_pcall(_L, 0, 0, 0)){
			_L = 0;
		}
		if (_L) _init = true;
	}

	HeroValue Role::get(const char* k) const{
		if (!_init) throw NotInitializeError();
		string key(k);
		if (_value.find(key) == _value.end()){
			lua_getglobal(_L, k);
			if (!lua_isnumber(_L, -1)) throw std::exception();
			_value[key] = lua_tonumber(_L, -1);
			lua_pop(_L, 1);
		}
		return _value[key];
	}

	const string& Role::name() const{
		if (!_init) throw NotInitializeError();
		return _name;
	}

}
