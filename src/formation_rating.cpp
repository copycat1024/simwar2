#include <iostream>
#include <exception>
#include <chrono>
#include <cmath>

#include "program.h"
#include "server.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::exception;

using namespace std::chrono;

using simwar::Program;
using simwar::Server;

char base32(int n){
	if (n<26){
		return 'A'+n;
	} else {
		return '2'+n-26;
	}
	throw exception();
}

void make_team(char* t, int n){
	t[1] = base32(n%32);
	t[0] = base32((n/32)%32);
}

int main(){
	Program p;
	string hero_path = p.folder() + "lua/default/hero/";
	Server ser;
	ser.init(hero_path);

	// Clock starts
	steady_clock::time_point time0 = steady_clock::now();

	int i, j, c = 0, r;
	char t1[8] = "AAaaaaa";
	char t2[8] = "AAaaaaa";
	for (i=0; i<126; i++){
		for (j=0; j<126; j++){
			if (i != j){
				make_team(t1, i);
				make_team(t2, j);
				c++;
				r = ser.run_battle_nl(t1, t2);
				cout << t1 << " " << t2 << " " << r << endl;
			}
		}
	}

	// Clock ends
	steady_clock::time_point time1 = steady_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(time1 - time0);
	double time = time_span.count();

	cerr << "Time elapsed: ";
	if (time > 1) cerr << floor(time) << "s ";
	if (time > 1) cerr << (time - floor(time))* 1000 << "ms";
	cerr << endl;
	cerr << "Battle cout:  " << c << endl;
}
