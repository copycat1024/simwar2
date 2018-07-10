#ifndef SW_ERROR_H
#define SW_ERROR_H

#include <exception>

namespace simwar{

	struct NotInitializeError: public std::exception{
		virtual const char* what() const noexcept {
			return "Variable not initialized";
		}
	};

}

#endif
