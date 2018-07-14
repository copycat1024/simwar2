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

	class Label: public Element {
		public:
			Label();
			void moveTo(int, int);
			void print();
			std::string text;
			Alignment align;
		private:
			bool _init;
	};

}

#endif
