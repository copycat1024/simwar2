#ifndef SW_LOGGER_H
#define SW_LOGGER_H

#include <string>
#include <iostream>
#include <set>
#include <utility>

#include "director.h"
#include "entity.h"
#include "battle.h"

typedef std::ostream SwLogStream;

namespace simwar {

	struct Logger {
		virtual void init(const Battle&) = 0;
		virtual void alter(int, int, HeroKey, HeroValue) = 0;
		virtual void set(int, int, HeroKey, HeroValue) = 0;
		virtual void turn(int, int) = 0;
		virtual void start(const char*) = 0;
		virtual void end() = 0;
		virtual void info() = 0;
	};

	struct LuaLogger: Logger {
		public:
			LuaLogger(SwLogStream&, Director&);
			void init(const Battle&);
			void alter(int, int, HeroKey, HeroValue);
			void set(int, int, HeroKey, HeroValue);
			void turn(int, int);
			void start(const char*);
			void end();
			void info();
		private:
			SwLogStream& _stream;
			Director& _dir;
			std::set<std::pair<HeroKey, HeroValue>> _val;

			void _val_info(HeroKey, HeroValue, std::string);
			void _key_info(HeroKey, std::string);
	};

}

#endif
