#include <iostream>
#include <exception>

#include "client.h"

#include "client/driver.h"
#include "client/element.h"

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

	cout << flush;
	waitkey();
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
			} else if (cmd != "exit"){
				cout << "Accepted command:" << endl;
				cout << "driver" << endl;
				cout << "ele (element)" << endl;
				cout << "exit" << endl;
			}
		} catch (exception& e){
			cout << "Error: "<< e.what() << endl;
		}
	} while (cmd != "exit");

	cout << "Simwar test exits." << endl;
	cout << endl;
}
