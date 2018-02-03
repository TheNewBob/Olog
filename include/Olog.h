#pragma once
#include <functional>

enum OLOGLEVEL
{
	OLOG_TRACE,
	OLOG_DEBUG,
	OLOG_INFO,
	OLOG_WARN,
	OLOG_ERROR
};

class Olog
{
public:
	Olog();
	~Olog();

	static OLOGLEVEL loglevel;
	static OLOGLEVEL assertlevel;

	static void setLogLevelFromFile(FILEHANDLE file);

	static char* projectName;

	static void trace(char *message, ...);
	static void debug(char *message, ...);
	static void info(char *message, ...);
	static void warn(char *message, ...);
	static void error(char *message, ...);

	static void assertThat(std::function<bool()> predicate, char *message, ...);

private:
	static void logMessage(char *message, char *level);
};

