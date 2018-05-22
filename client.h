#ifndef CLIENT_H
#define CLIENT_H

#include <stack>
#include <string>

struct LineSeg{
    int team;
    int pos;
    int line;
};

class Client{
public:
	Client(const char* filename);
    void show();
private:
	void _line(int line, const char* data);
	void _line(int line, std::string data);
	void _line(int line, int data);
	void _frame();
	void _run_log();
    int _len, _hei;
    int _team, _pos;
	std::string _file;
	std::stack<LineSeg> _seg;
};

#endif
