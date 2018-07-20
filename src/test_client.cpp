#include <iostream>
#include <exception>

#include "client.h"

#include "client/driver.h"
#include "client/label.h"
#include "client/progress_bar.h"
#include "client/board.h"
#include "client/client_control.h"

using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::exception;
using namespace simwar;
using namespace simwar::driver;

void testDriver(){
	int i;

	clrscr();
	for (i=0; i<8; i++){
		gotoxy(2+i, 1);
		cout << '_';
	}
	for (i=0; i<8; i++){
		setColor(i);
		gotoxy(2+i, 2);
		cout << i;
	}
	resetColor();
	for (i=0; i<8; i++){
		setBackgroundColor(i);
		gotoxy(2+i, 3);
		cout << i;
	}
	resetColor();
	cout << flush;
	waitkey();

	clrscr();
}

void testElement(){
	Label lab0, lab1, lab2, lab3;
	ProgressBar bar0, bar1, bar2;

	clrscr();

	lab0.moveTo(2, 2);
	lab0.text = "abcde1234567";
	lab0.align = Alignment::Left;
	lab0.print();

	lab1.moveTo(2, 3);
	lab1.text = "left";
	lab1.align = Alignment::Left;
	lab1.print();

	lab2.moveTo(2, 4);
	lab2.text = "center";
	lab2.align = Alignment::Center;
	lab2.print();

	lab3.moveTo(2, 5);
	lab3.text = "right";
	lab3.align = Alignment::Right;
	lab3.print();

	bar0.moveTo(2, 7);
	bar0.text = "24";
	bar0.align = Alignment::Center;
	bar0.fcolor = Color::White;
	bar0.bcolor = Color::Red;
	bar0.value = 24;
	bar0.print();

	bar1.moveTo(2, 8);
	bar1.text = "50";
	bar1.align = Alignment::Center;
	bar1.fcolor = Color::White;
	bar1.bcolor = Color::Red;
	bar1.value = 50;
	bar1.print();

	bar2.moveTo(2, 9);
	bar2.text = "75";
	bar2.align = Alignment::Center;
	bar2.fcolor = Color::White;
	bar2.bcolor = Color::Red;
	bar2.value = 75;
	bar2.print();

	gotoxy(1,1);
	cout << flush;
	waitkey();
	clrscr();
}

void testBoard(){
	Board board0;

	clrscr();

	board0.moveTo(2, 2);
	board0.slot_height = 5;
	board0.print();

	cout << flush;
	waitkey();
	clrscr();
}

void testControl(){
	ClientControl con;
	con.run("log.lua");
	clrscr();
}

int main(){
	string cmd;

	cout << "Simwar test" << endl;

	// Console loop
	do {
		cout << endl;
		cout << ">> "; getline(cin, cmd);

		try {
			if (cmd == "driver") {
				testDriver();
			} else if (cmd == "ele"){
				testElement();
			} else if (cmd == "board"){
				testBoard();
			} else if (cmd == "control"){
				testControl();
			} else if (cmd != "exit"){
				cout << "Accepted command:" << endl;
				cout << "driver  (driver)" << endl;
				cout << "ele     (element)" << endl;
				cout << "board   (board)" << endl;
				cout << "control (control)" << endl;
				cout << "exit" << endl;
			}
		} catch (exception& e){
			cout << "Error: "<< e.what() << endl;
		}
	} while (cmd != "exit");

	cout << "Simwar test exits." << endl;
	cout << endl;
}
