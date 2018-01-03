#include <windows.h>

#include "Debug.h"

void Debug::vaLog(const char* format, std::va_list arguments) {
	const uint32_t MAX_CHARS = 1024;
	static char buffer[MAX_CHARS];

	vsnprintf(buffer, MAX_CHARS, format, arguments);

	OutputDebugString(buffer);
}

void Debug::log(const char* format, ...) {
	std::va_list arguments;
	va_start(arguments, format);

	vaLog(format, arguments);

	va_end(arguments);
}

