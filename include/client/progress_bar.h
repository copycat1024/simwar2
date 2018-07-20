#ifndef SW_PROGRESS_BAR_H
#define SW_PROGRESS_BAR_H

#include <string>
#include "element.h"

namespace simwar {

	class ProgressBar: public Element {
		public:
			ProgressBar();
			void moveTo(int, int);
			void print();
			int max, value;
			int fcolor, bcolor;
			std::string text;
			Alignment align;
		private:
			bool _init;
	};

}

#endif
