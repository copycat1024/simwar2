#ifndef SW_LABEL_H
#define SW_LABEL_H

#include <string>
#include "element.h"

namespace simwar {

	class Label: public Element {
		public:
			Label();
			void moveTo(int, int);
			void print();
			std::string text;
			int fcolor, bcolor;
			Alignment align;
		private:
			bool _init;
	};

}

#endif
