#ifndef SW_BOARD_H
#define SW_BOARD_H

#include "element.h"

namespace simwar {

	class Board: public Element {
		public:
			Board();
			void moveTo(int, int);
			void print();

			int teamWidth()  const;
			int teamHeight() const;

			int slotLeft(int, int) const;
			int slotTop(int, int)  const;

			int pad_height, pad_width;
			int slot_width, slot_height;
			int river_width;
			int back_color, slot_color, river_color;
	};

}

#endif
