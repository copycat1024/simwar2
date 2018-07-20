#ifndef SW_CLIENT_CONTROL_H
#define SW_CLIENT_CONTROL_H

extern "C" {
#include "lua.h"
}

#include "client_model.h"
#include "client_view.h"

namespace simwar {

	struct ClientControl {
		public:
			ClientControl();
			~ClientControl();
			void run(const char*);

		private:
			ClientModel _model;
			ClientView  _view;
			lua_State*  _L;

			void _load(const char*);
			void _call(const char*);
			void _print();

			ClientModel& operator=(const ClientControl&) = delete;
	};

}

#endif
