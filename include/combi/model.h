#ifndef SW_COMBI_MODEL_H
#define SW_COMBI_MODEL_H

#include <array>
#include <string>

namespace simwar {

	typedef std::array<int, 5> Array5;

	struct TeamSetup {
		Array5 formation;
		Array5 heroes;		
	};

}

#endif
