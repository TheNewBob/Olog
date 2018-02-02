#include <stdio.h>
#include <stdarg.h>
#include <string>
#include "Orbitersdk.h"
#include "Olog.h"
#include <exception>
#include <Windows.h>

OLOGLEVEL Olog::loglevel = OLOG_INFO;
OLOGLEVEL Olog::assertlevel = OLOG_DEBUG;
char *Olog::projectName = "Olog";

Olog::Olog()
{
}


Olog::~Olog()
{
}

void Olog::trace(char* message, ...)
{
	if (OLOG_TRACE >= loglevel)
	{
		char logmessage[2056];
		va_list varargs;
		va_start(varargs, message);
		vsprintf_s(logmessage, 2056, message, varargs);
		va_end(varargs);
		logMessage(logmessage, "TRACE");
	}
}

void Olog::debug(char* message, ...)
{
	if (OLOG_DEBUG >= loglevel)
	{
		char logmessage[2056];
		va_list varargs;
		va_start(varargs, message);
		vsprintf_s(logmessage, 2056, message, varargs);
		va_end(varargs);
		logMessage(logmessage, "DEBUG");
	}
}

void Olog::info(char* message, ...)
{
	if (OLOG_INFO >= loglevel)
	{
		char logmessage[2056];
		va_list varargs;
		va_start(varargs, message);
		vsprintf_s(logmessage, 2056, message, varargs);
		va_end(varargs);
		logMessage(logmessage, "INFO");
	}
}

void Olog::warn(char* message, ...)
{
	if (OLOG_WARN >= loglevel)
	{
		char logmessage[2056];
		va_list varargs;
		va_start(varargs, message);
		vsprintf_s(logmessage, 2056, message, varargs);
		va_end(varargs);
		logMessage(logmessage, "!WARNING!");
	}
}

void Olog::error(char* message, ...)
{
	if (OLOG_ERROR >= loglevel)
	{
		char logmessage[2056];
		va_list varargs;
		va_start(varargs, message);
		vsprintf_s(logmessage, 2056, message, varargs);
		va_end(varargs);
		logMessage(logmessage, "!!ERROR!!");
	}

}

void Olog::assertThat(std::function<bool()> predicate, char *message, ...)
{
	if (assertlevel >= loglevel)
	{
		if (!predicate())
		{
			char logmessage[2056];
			va_list varargs;
			va_start(varargs, message);
			vsprintf_s(logmessage, 2056, message, varargs);
			va_end(varargs);
			std::string msg = "Assertion failed: ";
			msg += logmessage;
			logMessage((char*)msg.data(), "!!ERROR!!");
			throw std::runtime_error("Olog Assertion failed, see log for details!");
		}
	}
}


void Olog::logMessage(char *message, char* loglevel)
{
	std::string finalMessage = projectName;
	finalMessage += ":[";
	finalMessage += loglevel;
	finalMessage += "] ";
	finalMessage += message;
	oapiWriteLog((char*)finalMessage.data());
}




