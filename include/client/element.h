#ifndef SW_ELEMENT_H
#define SW_ELEMENT_H

#include <string>

namespace simwar {

	struct Element {
		int left, top, width, height;
	};

	enum class Alignment: int {
		Left,
		Center,
		Right
	};

}

#endif
