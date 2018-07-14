#include <iostream>
#include "driver.h"
#include "element.h"

using namespace simwar::driver;
using std::cout;

namespace simwar {

	Label::Label(){
		left   = 1;
		top    = 1;
		width  = 10;
		height = 1;
		align  = Alignment::Left;
	}

	void Label::moveTo(int new_left, int new_top){
		top = new_top;
		left = new_left;
	}

	void Label::print(){
		int len, off, sz = text.size();
		if (width > sz){
			len = sz;
			if (align == Alignment::Left){
				off = left;
			} else if (align == Alignment::Right) {
				off = left + width - sz;
			} else {
				off = left + (width - sz)/2;
			}
		} else {
			len = width;
			off = left;
		}
		
		for (int i=0; i<len; i++){
			gotoxy(off+i, top);
			cout << text[i];
		}
	}

}
