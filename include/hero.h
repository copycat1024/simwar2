#ifndef HERO_H
#define HERO_H

#include "sol.hpp"
#include "entity.h"

enum class SwHeroKey:EntityKey{
	// Debug index
	DB = 0x0000,

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
	inline EntityValue hp(){
		return (*this)[SwHeroKey::HP];
	}
	inline EntityValue id(){
		return (*this)[SwHeroKey::ID];
	}
	inline bool isDead(){
		return hp()<=0;
	}
	void alter(SwHeroKey, EntityValue);
};

class SwBattle;
class SwBattleHero:virtual public SwHero, virtual LuaEntity{
private:
	const char* _locateHeroFile(SwBattle* bat, int id);
	void _logAlter(SwHeroKey, EntityValue);
	void _load(SwHeroKey, const char*);
	void _alter(SwHeroKey, EntityValue);
	int _targetSingle();
	SwBattle* _bat;
protected:
	friend SwBattle;
	SwBattleHero(SwBattle* bat, int id);
    void turn();
};

#endif
