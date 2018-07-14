#ifndef SW_SERVER_H
#define SW_SERVER_H

#include <string>
#include "server/logger.h"
#include "server/director.h"

namespace simwar {

	class Server {
		public:
			void init(const std::string&);
			int run_battle(const std::string&, const std::string&, SwLogStream&);
			int run_battle(const std::string&, const std::string&, const char*);
			int run_battle(const std::string&, const std::string&);
			int run_battle_nl(const std::string&, const std::string&);
		private:
			Director _dir;
	};

}

#endif
