#ifndef SW_DIRECTOR_H
#define SW_DIRECTOR_H

#include <string>
#include <vector>

#include "role.h"

namespace simwar {

	class Director {
	public:
		Director();
		void init(std::string);
		const std::vector<std::string>& hero_files() const;
		const std::vector<Role>& hero_roles() const;
	private:
		bool _init;
		std::vector<std::string> _hero_files;
		std::vector<Role> _hero_roles;
	};

}

#endif
