#ifndef CLIENT_H
#define CLIENT_H

#include <string>

// ncurses wrapper for SwClient
class ClientWrap{
protected:
	ClientWrap();
    int _len, _hei;
	void _frame();
	void _line(int, int, int, const char*);
	void _line(int, int, int, std::string);
	void _line(int, int, int, int);
	void _pause();
};

class SwClient:ClientWrap{
public:
	SwClient(const char* filename);
    void show();
private:
	void _run_log();
    int _team, _pos;
	std::string _file;
};

#endif
