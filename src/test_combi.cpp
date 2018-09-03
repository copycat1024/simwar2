#include <iostream>
#include <iomanip>
#include <exception>

#include "combi.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::flush;
using std::string;
using std::exception;
using namespace simwar;

void testPrint(){
	int i;
	for (i=0; i<126; i++){
		Array5 a = intToFormation(i);
		int    n = formationToInt(a);
		cout << setw(3) << i << " ";
		printArr(a);
		cout << " " << setw(3) << n;
		cout << endl;
	}
}

void testConvert(){
	TeamSetup setup;
	string stamp;

	stamp = "A5al3ba";
	setup = stampToSetup(stamp);
	cout << stamp << endl;
	cout << setupToStamp(setup) << endl;

	stamp = "DSabbbabbbab";
	setup = stampToSetup(stamp);
	cout << stamp << endl;
	cout << setupToStamp(setup) << endl;
}

int main(){
	string cmd;

	cout << "Simwar test" << endl;

	// Console loop
	do {
		cout << endl;
		cout << ">> "; getline(cin, cmd);

		try {
			if (cmd == "print") {
				testPrint();
			} else if (cmd == "convert") {
				testConvert();
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
