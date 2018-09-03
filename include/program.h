#ifndef SW_PROGRAM_H
#define SW_PROGRAM_H

#include <string>

#include "server.h"
#include "client.h"

namespace simwar {

	class Program {
	public:
		Program();
		void init();
		const std::string& path();
		const std::string& folder();

		int battleToFile(const std::string&, const std::string&, const std::string&);
		int battleNoLog(const std::string&, const std::string&);
		void clientFromFile(const std::string&);

		void execute(int, char**);

	private:
		bool _init;
		std::string _path;
		std::string _folder;
		Server _server;
		ClientControl _client;
		static const char* _default_log_file;

		void _init_path();
		void _init_server();

		void _printHelp(const std::string&);
	};

}

#endif
