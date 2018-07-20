#ifndef SW_CLIENT_MODEL_H
#define SW_CLIENT_MODEL_H

extern "C" {
#include "lua.h"
}

#include "server/entity.h"

namespace simwar {

	struct ClientView;

	struct ClientModel {
		ClientView* view;

		void turn(lua_State*);
		void set(lua_State*);
		void alter(lua_State*);
		void valInfo(lua_State*);
		void keyInfo(lua_State*);

		std::array<std::array<Hero, 5>, 2> teams;
		ValueInfoTable val_info;
		RevKeyInfoTable key_info;
	};

}

#endif
