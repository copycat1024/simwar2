#ifndef SW_API_H
#define SW_API_H

extern "C" {
#include "lua.h"
}

namespace simwar {

	namespace api {
		void load(lua_State*);
	}

}

#endif
