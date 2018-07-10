/*
#include "entity.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

namespace simwar{

	void Entity::alter(EntityKey k, EntityValue v){
		(*this)[k] += v;
	}

	LuaEntity::LuaEntity(const string filename){
		_lua.script_file(filename.c_str());
	}

	void LuaEntity::load(EntityKey k, const char* varname){
		(*this)[k] = _lua[varname];
	}

}
*/
