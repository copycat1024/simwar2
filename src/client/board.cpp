#include <iostream>
#include "driver.h"
#include "board.h"

using namespace simwar::driver;
using std::cout;


namespace simwar {

	Board::Board(){
		left   = 1;
		top    = 1;

		slot_width  = 10;
		slot_height = 3;

		river_width = 5;

		pad_height  = 1;
		pad_width   = 2;

		back_color  = Color::Yellow;
		slot_color  = Color::Green;
		river_color = Color::Blue;
	}

	void Board::moveTo(int new_left, int new_top){
		top = new_top;
		left = new_left;
	}

	int Board::teamHeight() const{
		return 3*slot_height + 4*pad_height;
	}

	int Board::teamWidth() const{
		return 3*slot_width  +  4*pad_width;
	}

	int Board::slotLeft(int team, int pos) const {
		int i = team == 0 ? 2-pos/3 : pos/3;
		int slot_left = left + (slot_width  +  pad_width)*i +  pad_width;
		if (team == 1) slot_left += teamWidth() + river_width;
		return slot_left;
	}

	int Board::slotTop(int team, int pos) const {
		return top  + (slot_height + pad_height)*(pos%3) + pad_height;
	}

	void Board::print(){
		// draw background
		setBackgroundColor(back_color);
		drawRect(left, top, 2*teamWidth()+river_width, teamHeight());

		// draw river
		setBackgroundColor(river_color);
		drawRect(left+teamWidth(), top, river_width, teamHeight());

		setBackgroundColor(slot_color);
		for (int i=0; i<9; i++){
			drawRect(slotLeft(0, i), slotTop(0, i), slot_width, slot_height);
			drawRect(slotLeft(1, i), slotTop(1, i), slot_width, slot_height);
		}

		gotoxy(1,1);

		resetColor();
	}

	void Board::drawRect(int left, int top, int width, int height){
		for (int x=0; x<width; x++){
			for (int y=0; y<height; y++){
				gotoxy(left+x, top+y);
				cout << ' ';
			}
		}
	}

}
