#ifndef SW_DRIVER_H
#define SW_DRIVER_H

namespace simwar {

	namespace driver {
		void clrscr();
		void gotoxy(int, int);
		int waitkey();
		int getkey();

		void resetColor();
		void setColor(int);
		void setBackgroundColor(int);

		namespace Color {
			const int Black  = 0;
			const int Red    = 1;
			const int Yellow = 2;
			const int Green  = 3;
			const int Blue   = 4;
			const int Purple = 5;
			const int Cyan   = 6;
			const int White  = 7;
		}

	}

}

#endif
