#include <iostream>
#include <exception>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "client_control.h"
#include "driver.h"

using std::cout;
using std::endl;
using namespace simwar::driver;

namespace simwar {

	typedef void (ClientModel::*model_func)(lua_State * L);

	// This template wraps a member function into a C-style "free" function compatible with lua.
	template <model_func func>
	int dispatch(lua_State * L) {
		ClientModel * ptr = *static_cast<ClientModel**>(lua_getextraspace(L));
		((*ptr).*func)(L);
		return 0;
	}

	void ClientControl::run(const char* file_name){
		_load(file_name);

		_model.view = &_view;

		_call("info");
		_call("init");
		_call("run");

		_view.print(_model);
	}

	void ClientControl::_load(const char* file_name){
		if (!_L) lua_close(_L);

		_L = luaL_newstate();

		if (luaL_loadfile(_L, file_name)){
			_L = 0;
			throw std::exception();
		}

		if (lua_pcall(_L, 0, 0, 0)){
			_L = 0;
			throw std::exception();
		}

		ClientModel** p = static_cast<ClientModel**>(lua_getextraspace(_L));
		*p = &_model;

		lua_register(_L, "turn",     &dispatch<&ClientModel::turn>);
		lua_register(_L, "set",      &dispatch<&ClientModel::set>);
		lua_register(_L, "alter",    &dispatch<&ClientModel::alter>);
		lua_register(_L, "val_info", &dispatch<&ClientModel::valInfo>);
		lua_register(_L, "key_info", &dispatch<&ClientModel::keyInfo>);
	}

	void ClientControl::_call(const char* key){
		lua_getglobal(_L, key);
		if (lua_pcall(_L, 0, 0, 0) != 0) throw std::exception();
	}

	ClientControl::ClientControl(){
		_model.view = 0;
	}

	ClientControl::~ClientControl(){
		if (_L) lua_close(_L);
	}

}
