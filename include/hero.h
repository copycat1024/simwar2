#ifndef HERO_H
#define HERO_H

#include "sol.hpp"
#include "entity.h"

enum class SwHeroKey:int{
	// Hero info
    HP = 0x0001, // hit point
    AD = 0x0002, // attack damage

    // Battle info
    ID = 0x0101, // ID
    PS = 0x0102, // position
};

class SwHero:virtual Entity{
public:
	EntityValue& operator[](SwHeroKey);
	EntityValue hp();
};

class SwBattle;
class SwBattleHero:virtual public SwHero, virtual LuaEntity{
private:
	void _load(SwHeroKey, const char*);
	const char* _locateHeroFile(SwBattle* bat, int id);
protected:
	friend SwBattle;
	SwBattleHero(SwBattle* bat, int id);
};

#endif
