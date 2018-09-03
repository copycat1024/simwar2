#include <iostream>
#include "program.h"

using namespace std;

int main(int argc, char** argv){

	simwar::Program p;

	p.init();

	p.execute(argc, argv);


	return 0;
}
