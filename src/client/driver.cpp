#include <cstdio>
#include <cstdlib>
#include <termios.h> // for getch() and kbhit()
#include <unistd.h> // for getch(), kbhit() and (u)sleep()
#include <sys/ioctl.h> // for getkey()
#include <sys/types.h> // for kbhit()
#include <sys/time.h> // for kbhit()

#include "driver.h"

namespace simwar {

	namespace driver {

		void clrscr(void) {
			// clear whole screen
			printf("\033[2J");

			// clear scroll back
			printf("\033[3J");

			// put cursor home
			printf("\033[H");

			// flush
			fflush(stdout);
		}

		void gotoxy(int x, int y) {
			printf("\033[%d;%df", y, x);
		}

		int getch(void) {
			// Here be magic.
			struct termios oldt, newt;
			int ch;
			tcgetattr(STDIN_FILENO, &oldt);
			newt = oldt;
			newt.c_lflag &= ~(ICANON | ECHO);
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);
			ch = getchar();
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
			return ch;
		}

		void msleep(unsigned int ms) {
			// usleep argument must be under 1 000 000
			if (ms > 1000) sleep(ms/1000000);
			usleep((ms % 1000000) * 1000);
		}

		int kbhit(void) {
			// Here be dragons.
			static struct termios oldt, newt;
			int cnt = 0;
			tcgetattr(STDIN_FILENO, &oldt);
			newt = oldt;
			newt.c_lflag    &= ~(ICANON | ECHO);
			newt.c_iflag     = 0; // input mode
			newt.c_oflag     = 0; // output mode
			newt.c_cc[VMIN]  = 1; // minimum time to wait
			newt.c_cc[VTIME] = 1; // minimum characters to wait for
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);
			ioctl(0, FIONREAD, &cnt); // Read count
			struct timeval tv;
			tv.tv_sec  = 0;
			tv.tv_usec = 100;
			select(STDIN_FILENO+1, NULL, NULL, NULL, &tv); // A small time delay
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
			return cnt; // Return number of characters
		}

		int waitkey(){
			while (!kbhit()) msleep(50);
			return getkey();
		}

		int getkey(void) {
			int cnt = kbhit(), i, c=0;
			if (cnt > 4){
				clrscr();
				printf("kbhit returns more than 4\n");
				exit(1);
			}
			for (i=0; i<cnt; i++){
				c <<= 8;
				c += getch();
			}
			return c;
		}

		void resetColor(){
			printf("\033[0m");
		}

		void setColor(int color){
			printf("\033[3%dm", color);
		}

		void setBackgroundColor(int color){
			printf("\033[4%dm", color);
		}

	}

}
