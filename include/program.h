#ifndef SW_PROGRAM_H
#define SW_PROGRAM_H

#include <string>

namespace simwar {

	class Program {
	public:
		Program();
		void init();
		void run_battle(const char*, const char*, const char*);
		const std::string& path();
		const std::string& folder();
	private:
		bool _init;
		std::string _path;
		std::string _folder;
	};

}

#endif
