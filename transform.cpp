#include "solRowMinLex.h"
#include "pencilmarks.h"
#include "options.h"
#include "fsss2.h"
#include "minimizer.h"

int transform::cmdSolRowMinLex() {
	int ret = 0;
	char line[2000];
	char outPuz[729];
	char sol[88];
	fsss2::getAnySolution solver;
	bool vanilla = opt.getFlag("vanilla");
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(vanilla) {
			pm.fromChars81(line);
		}
		else {
			if(!pm.fromChars729(line)) {
				ret = 1;
				continue;
			}
		}
		pencilmarks res;
		if(!solver.solve(pm, sol)) {
			ret = 1;
			continue; //silently ignore invalid puzzles
		}
		solRowMinLex::pmMinLex(pm, sol, res);
		res.toChars729(outPuz);
		printf("%729.729s\n", outPuz);
	}
	return ret;
}
int transform::cmdMinimizeRandom() {
	int ret = 0;
	char line[2000];
	bool vanilla = opt.getFlag("vanilla");
	int bufSize = opt.getIntValue("buffersize", 0);
	bool randomShots = (bufSize == 0);
	int numResults = opt.getIntValue("numresults", 10);
	int minSize = opt.getIntValue("minsize", 0);
	int maxSize = opt.getIntValue("maxsize", 729);
	int maxAttempts = opt.getIntValue("maxattempts", INT_MAX);
	int maxRetries = opt.getIntValue("maxretries", INT_MAX);
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(vanilla) {
			pm.fromChars81(line);
			//char curPuz[88];
			//for(int i = 0; i < 81; i++) curPuz[i] = (line[i] <= '9' && line[i] > '0' ? line[i] - '0' : 0);
			//minimizer::minimizePencilmarks(curPuz, bufSize);
		}
		else {
			if(!pm.fromChars729(line)) {
				ret = 1;
				continue;
			}
			//minimizer::minimizePencilmarks(pm, bufSize);
		}
		if(randomShots) {
			minimizer::minimizeRandom(pm, numResults, minSize, maxSize, maxAttempts, maxRetries);
		}
		else {
			minimizer::minimizePencilmarks(pm, bufSize);
		}
	}
	return ret;
}

