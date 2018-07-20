#include <iostream>
#include <exception>
#include "driver.h"
#include "progress_bar.h"

using namespace simwar::driver;
using std::cout;

namespace simwar {

	ProgressBar::ProgressBar(){
		left   = 1;
		top    = 1;
		width  = 10;
		height = 1;
		align  = Alignment::Left;
		fcolor = Color::White;
		bcolor = Color::Black;
		max = 100;
		value = 50;
	}

	void ProgressBar::moveTo(int new_left, int new_top){
		top = new_top;
		left = new_left;
	}

	void ProgressBar::print(){
		if (max == 0) throw std::exception();
		int len, off, sz = text.size();
		int cut = (2*width*value+max)/(2*max);

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

		for (int i=0; i<width; i++){
			gotoxy(left+i, top);
			if (i<cut){ 
				setBackgroundColor(bcolor);
			} else {
				setBackgroundColor(fcolor);
			}
			cout << ' ';
		}

		for (int i=0; i<len; i++){
			gotoxy(off+i, top);
			if (off-left+i<cut){ 
				setColor(fcolor);
				setBackgroundColor(bcolor);
			} else {
				setColor(bcolor);
				setBackgroundColor(fcolor);
			}
			cout << text[i];
		}
		resetColor();
	}

}
