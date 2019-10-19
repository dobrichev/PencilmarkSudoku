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
			minimizer::minimizePencilmarks(pm, bufSize, numResults, minSize, maxSize);
		}
	}
	return ret;
}
int transform::cmdMaximizeRandom() {
	int ret = 0;
	char line[2000];
	int numResults = opt.getIntValue("numresults", 10);
	int minImprovement = opt.getIntValue("minimprovement", 1);
	int maxAttempts = opt.getIntValue("maxattempts", INT_MAX);
	int maxRetries = opt.getIntValue("maxretries", INT_MAX);
	int numCluesToAdd = opt.getIntValue("addclues", 9);
	int numAddAttempts = opt.getIntValue("addattempts", 600);
	fsss2::getAnySolution solver;
	char sol[88];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		if(!solver.solve(pm, sol)) {
			ret = 1;
			continue; //silently ignore invalid puzzles
		}
		int minSize = pm.popcount() + minImprovement;
		for(int i = 0; i < numAddAttempts; i++) {
			pencilmarks pm1(pm);
			minimizer::addRandomRestrictions(pm1, sol, numCluesToAdd);
			minimizer::minimizeRandom(pm1, numResults, minSize, 729, maxAttempts, maxRetries);
		}
	}
	return ret;
}
int transform::cmdAddRedundant() {
	int ret = 0;
	char line[2000];
	int numCluesToAdd = opt.getIntValue("numclues", 1);
	if(numCluesToAdd <= 0) return 1;
	fsss2::getAnySolution solver;
	char sol[88];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		if(!solver.solve(pm, sol)) {
			ret = 1;
			continue; //silently ignore invalid puzzles
		}
		minimizer::addClues(pm, sol, numCluesToAdd, 0);
		fflush(NULL);
	}
	return ret;
}
int transform::cmdRemoveClues() {
	int ret = 0;
	char line[2000];
	int numCluesToRemove = opt.getIntValue("numclues", 1);
	if(numCluesToRemove <= 0) return 1;
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		minimizer::removeClues(pm, numCluesToRemove, 0);
		fflush(NULL);
	}
	return ret;
}
int transform::cmdSize() {
	int ret = 0;
	char line[2000];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		char outPuz[729];
		pm.toChars729(outPuz);
		printf("%729.729s\t%d\n", outPuz, pm.popcount());
	}
	return ret;
}


