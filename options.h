#ifndef OPTIONS_H_INCLUDED

#define OPTIONS_H_INCLUDED

#define _CRT_SECURE_NO_DEPRECATE

//#include "tables.h"
#include <limits.h>
#include <memory.h>

#include "anyoption.h"

//commands
#include "cmdSolve.h"
#include "cmdBackdoor.h"

class options {
	AnyOption anyopt;
	time_t startTime;
public:
	bool verbose;
	options();
	bool read(int argc, char* argv[]);
	int execCommand();
	void printUsage();
	const char* getValue(const char* key);
	int getIntValue(const char* key, const int defaultValue);
	bool getFlag(const char* key);
	const char* getStartTime() const;
};

extern options opt;

#endif // OPTIONS_H_INCLUDED
