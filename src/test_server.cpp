#include <iostream>
#include <string>
#include <exception>

#include "program.h"
#include "server.h"

#include "server/director.h"
#include "server/team.h"
#include "server/proxy.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::exception;

using namespace simwar;

void testProgram(){
	cout << "Program class unit test:" << endl;
	Program p;
	cout << "Executable file path:   " << p.path() << endl;
	cout << "Executable folder path: " << p.folder() << endl;
}

void testDirector(){
	Program p;
	string hero_path = p.folder() + "lua/default/hero/";

	cout << "Director class unit test:" << endl;
	cout << "Hero folder path: " << hero_path  << endl;

	Director d;
	d.init(hero_path);
	cout << "Hero files:" << endl;
	for (auto f: d.hero_files()){
		cout << "- " << f << endl;
	}
}

void testRole(){
	Program p;
	string hero_path = p.folder() + "lua/default/hero/";

	cout << "Role class unit test:" << endl;
	cout << "Hero folder path: " << hero_path  << endl;

	Director d;
	d.init(hero_path);
	cout << "Heroes:" << endl;
	for (auto& r: d.hero_roles()){
		cout << "- " << r.name() << " hp: " << r.get("hp") << endl;
	}
}

void testTeam(){

	Program p;
	string hero_path = p.folder() + "lua/default/hero/";

	Director d;
	d.init(hero_path);

	cout << "Team class unit test:" << endl;

	Team t;
	string stamp("ABababa"); 
	cout << "Stamp: " << stamp << endl;
	t.init(stamp);

	TeamSetup s = t.setup;
	cout << "Formation: ";
	for (int n: s.formation) cout << n << ' ';
	cout << endl;
	cout << "Heroes:    ";
	for (int n: s.heroes) cout << n << ' ';
	cout << endl;
}

void testProxy(){

	Program p;
	string hero_path = p.folder() + "lua/default/hero/";

	Director d;
	d.init(hero_path);

	cout << "Proxy class unit test:" << endl;

	Proxy proxy(d);
	LuaLogger log(cout, d);
	proxy.log = &log;
	proxy.run_battle("ABababa", "ABababa");
}

void testServer(){

	int res;
	Program p;
	string hero_path = p.folder() + "lua/default/hero/";

	cout << "Proxy class unit test:" << endl;

	Server ser;
	ser.init(hero_path);
	res = ser.run_battle("ABababa", "ABababa");
	cout << res << endl;
	res = ser.run_battle_nl("ABababa", "ABababa");
	cout << res << endl;
	res = ser.run_battle("ABababa", "ABababa", "log.lua");
	cout << res << endl;
}

int main(){
	string cmd;

	cout << "Simwar test" << endl;

	// Console loop
	do {
		cout << endl;
		cout << ">> "; getline(cin, cmd);

		try {
			if (cmd == "prog") {
				testProgram();
			} else if (cmd == "dir"){
				testDirector();
			} else if (cmd == "role"){
				testRole();
			} else if (cmd == "team"){
				testTeam();
			} else if (cmd == "proxy"){
				testProxy();
			} else if (cmd == "server"){
				testServer();
			} else if (cmd != "exit"){
				cout << "Accepted command:" << endl;
				cout << "exit" << endl;
				cout << "prog   (program)" << endl;
				cout << "dir    (director)" << endl;
				cout << "role   (director-role)" << endl;
				cout << "team   (team)" << endl;
				cout << "proxy  (proxy)" << endl;
				cout << "server (server)" << endl;
			}
		} catch (exception& e){
			cout << "Error: "<< e.what() << endl;
		}
	} while (cmd != "exit");

	cout << "Simwar test exits." << endl;
	cout << endl;
}
