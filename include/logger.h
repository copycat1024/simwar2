#ifndef SW_LOGGER_H
#define SW_LOGGER_H

namespace simwar{

	struct Logger {
		virtual void logAlter() = 0;
		virtual void logInit() = 0;
	}

	struct EmptyLogger {
		virtual void logAlter(){}
	}

}

#endif
