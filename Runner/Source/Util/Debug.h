#pragma once

#include <string>
#include <iostream>
#include <cstdarg>
#include <cstdio>

class Debug 
{
private:
	static void vaLog(const char* format, std::va_list arguments);
public:
	static void log(const char* format, ...);
};