#include "entity.h"
#include <iostream>
#include <cstring>

using std::strtok;
using std::cout;
using std::endl;

void Entity::alter(EntityKey k, EntityValue v){
	(*this)[k] += v;
}

LuaEntity::LuaEntity(const char* filename){
    char* buf = new char[strlen(filename)];
    strcpy(buf, filename);
	_lua.script_file(buf);
	delete [] buf;
}

void LuaEntity::load(EntityKey k, const char* varname){
	(*this)[k] = _lua[varname];
}
