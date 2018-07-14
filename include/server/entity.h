#ifndef SW_ENTITY_H
#define SW_ENTITY_H

#include <unordered_map>

namespace simwar{

	typedef unsigned int HeroKey;
	typedef int HeroValue;
	typedef std::unordered_map<HeroKey, HeroValue> Hero;

	namespace Key{
		const HeroKey ID   = 0;
		const HeroKey HID  = 1; // hero ID
		const HeroKey Pos  = 2;

		const HeroKey HP   = 8;
		const HeroKey AD   = 9;
	}

}

#endif
