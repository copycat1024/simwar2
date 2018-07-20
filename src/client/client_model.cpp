#include <iostream>
#include <string>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "client_model.h"
#include "client_view.h"

using std::cout;
using std::endl;
using std::string;

namespace simwar {
	AlterDatum::AlterDatum(){
	}

	AlterDatum::AlterDatum(int team, int id, HeroKey key, HeroValue val)
	: team(team), id(id), key(key), val(val){
	}

	void ClientModel::alter(lua_State* L){
		if (lua_gettop(L) != 4)  throw std::exception();
		if (!lua_isnumber(L, 1)) throw std::exception();
		if (!lua_isnumber(L, 2)) throw std::exception();
		if (!lua_isnumber(L, 3)) throw std::exception();
		if (!lua_isnumber(L, 4)) throw std::exception();

		int team = lua_tonumber(L, 1);
		int id   = lua_tonumber(L, 2);
		int key  = lua_tonumber(L, 3);
		int val  = lua_tonumber(L, 4);

		teams[team][id][key] += val;
		alter_data.push_back(AlterDatum(team, id, key, val));
	}

	void ClientModel::set(lua_State* L){
		if (lua_gettop(L) != 4)  throw std::exception();
		if (!lua_isnumber(L, 1)) throw std::exception();
		if (!lua_isnumber(L, 2)) throw std::exception();
		if (!lua_isnumber(L, 3)) throw std::exception();
		if (!lua_isnumber(L, 4)) throw std::exception();

		int team = lua_tonumber(L, 1);
		int id   = lua_tonumber(L, 2);
		int key  = lua_tonumber(L, 3);
		int val  = lua_tonumber(L, 4);

		teams[team][id][key] = val;
	}

	void ClientModel::turn(lua_State* L){
		if (lua_gettop(L) != 2)  throw std::exception();
		if (!lua_isnumber(L, 1)) throw std::exception();
		if (!lua_isnumber(L, 2)) throw std::exception();

		int team = lua_tonumber(L, 1);
		int id   = lua_tonumber(L, 2);

		if (view) view->print(*this);
		active_team = team;
		active_id   = id;
		alter_data.clear();

		if (view) view->print(*this);

	}

	void ClientModel::valInfo(lua_State* L){
		if (lua_gettop(L) != 3)  throw std::exception();
		if (!lua_isnumber(L, 1)) throw std::exception();
		if (!lua_isnumber(L, 2)) throw std::exception();
		if (!lua_isstring(L, 3)) throw std::exception();

		int key = lua_tonumber(L, 1);
		int val = lua_tonumber(L, 2);
		string val_name = string(lua_tostring(L, 3));

		val_info[key][val] = val_name;
	}

	void ClientModel::keyInfo(lua_State* L){
		if (lua_gettop(L) != 2)  throw std::exception();
		if (!lua_isnumber(L, 1)) throw std::exception();
		if (!lua_isstring(L, 2)) throw std::exception();

		int key = lua_tonumber(L, 1);
		string key_name = string(lua_tostring(L, 2));

		key_info[key_name] = key;
	}

}
