#ifndef SW_PROXY_H
#define SW_PROXY_H

#include "battle.h"
#include "logger.h"
#include "director.h"

namespace simwar {

	class Proxy {
		public:
			Battle battle;
			Logger* log;

			// for user
			Proxy(const Director&);
			int run_battle(const std::string&, const std::string&);

			// for api
			void alterAlly(int, HeroKey, HeroValue);
			void alterEnemy(int, HeroKey, HeroValue);
			void setAlly(int, HeroKey, HeroValue);
			void setEnemy(int, HeroKey, HeroValue);
		private:
			const Director& _dir;
			void _load_roles();
			void _call_roles();

			void _alter(int, int, HeroKey, HeroValue);
			void _set(int, int, HeroKey, HeroValue);

	};

}

#endif
