#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "solRowMinLex.h"
#include "pencilmarks.h"
#include "options.h"
#include "fsss2.h"

struct transform {
	static int cmdSolRowMinLex();
	static int cmdPatMinLex();
	static int cmdMinimizeRandom();
	static int cmdMaximizeRandom();
	static int cmdAddRedundant();
	static int cmdRemoveClues();
	static int cmdAddClues();
	static int cmdSize();
	static int cmdTwins();
	static int cmdClusterize();
};
#endif //TRANSFORM_H_
