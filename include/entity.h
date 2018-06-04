#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <unordered_map>
#include "sol.hpp"

typedef unsigned int EntityKey;
typedef int EntityValue;
typedef std::unordered_map<EntityKey, EntityValue> EntityBase;

class Entity:public EntityBase{
public:
    void alter(EntityKey, EntityValue);
};

class LuaEntity:virtual public Entity{
public:
    LuaEntity(std::string);
    void load(EntityKey, const char*);
private:
	sol::state _lua;
};

#endif
