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
			const int Green  = 2;
			const int Blue   = 8;
			const int Purple = 9;
			const int Cyan   = 2;
			const int White  = 2;
		}

	}

}

#endif
