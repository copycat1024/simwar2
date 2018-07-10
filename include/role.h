#ifndef SW_ROLE_H
#define SW_ROLE_H

#include <string>
#include <vector>
#include <unordered_map>

extern "C" {
#include "lua.h"
}

#include "entity.h"

namespace simwar{

	class Role {
	public:
		Role();
		~Role();
		void init(std::string);
		const std::string& name() const;
		HeroValue get(const char*) const;
	private:
		bool _init;
		std::string _name;
		lua_State* _L;
		mutable std::unordered_map<std::string, HeroValue> _value;

		// disable copying
		Role operator=(const Role&);
	};

}

#endif
