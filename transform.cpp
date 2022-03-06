#include <vector>
//#include <algorithm>

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
	int numCluesToAdd = opt.getIntValue("numclues", 9);
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
	int maxSolutionCount = opt.getIntValue("maxsolutioncount", 0);
	pencilmarks blacklist;
	const char* removeMaskPar = opt.getValue("removemask");
	if(removeMaskPar) {
		blacklist = pencilmarks::xMask81;
		pencilmarks removemask;
		removemask.fromList(removeMaskPar);
		blacklist.clearBits(removemask);
		//fprintf(stderr, "blacklist size=%d\n", blacklist.popcount());
	}
	const char* keepMaskPar = opt.getValue("keepmask");
	if(keepMaskPar) {
		pencilmarks keepmask;
		keepmask.fromList(keepMaskPar);
		blacklist |= keepmask;
	}
	//printf("removemask=[%s]\n", removeMaskPar);
	//printf("keepmask=[%s]\n", keepMaskPar);
	//exit(1);
	if(numCluesToRemove <= 0) return 1;
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		minimizer::removeClues(pm, numCluesToRemove, maxSolutionCount, 0, blacklist);
		fflush(NULL);
	}
	return ret;
}
int transform::cmdAddClues() {
	int ret = 0;
	char line[2000];
	int numCluesToAdd = opt.getIntValue("numclues", 1);
	if(numCluesToAdd <= 0) return 1;
	bool presolve = opt.getFlag("presolve");
	bool singleNonRedundant = opt.getFlag("singlenonredundant");
	bool fast = opt.getFlag("fast");
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		if(singleNonRedundant) {
			minimizer::addSingleNonRedundantClue(pm);
		}
		else if(fast) {
			minimizer::addCluesAnyGridFast(pm, numCluesToAdd, pencilmarks{});
		}
		else if(presolve) {
			minimizer::addCluesAnyGridPreSolve(pm, numCluesToAdd);
		}
		else {
			minimizer::addCluesAnyGrid(pm, numCluesToAdd, pencilmarks{});
		}
		//fflush(NULL);
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
int transform::cmdTwins() {
	int ret = 0;
	char line[2000];
	pencilmarks pmInverse;
	fsss2::getSingleSolution ss;
	fsss2::getNSolutions ms;
	char sol[88];
	pencilmarks origSol;
	//int constexpr max_sol(4000);
	int constexpr max_sol(40000000);
	pencilmarks* resPM = new pencilmarks[max_sol];
	char outPuz[729];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		//solve
		if(1 != ss.solve(pm, sol)) {
			ret = 1;
			continue;
		}
		bm128 emptyCells(constraints::mask81);
		for(int v = 0; v < 9; v++) {
			emptyCells.clearBits(pm[v]);
		}
		//pmInverse.clear();
		pmInverse = pm;
		for(int i = 0; i < 81; i++) {
			if(emptyCells.isBitSet(i)) {
				//no initial restrictions for this cell - leave only the solution bit empty
				for(int v = 0; v < 9; v++) {
					if(sol[i] - 1 == v) {
						pmInverse[v].clearBit(i);
					}
					else {
						pmInverse[v].setBit(i);
					}
				}
			}
			else {
				//some initial restrictions exist - allow all
				for(int v = 0; v < 9; v++) {
					pmInverse[v].clearBit(i);
				}
			}
		}
		//pm.toChars729(outPuz);
		//printf("%729.729s\tOriginal\n", outPuz);
		int numSol = ms.solve(pmInverse, resPM, max_sol);
		if(numSol >= max_sol) {
			//printf("Maximum of %d solutions reached\n", max_sol);
			//printf("Maximum of %d solutions reached, skipping\n", max_sol);
			//continue;
		}
		if(numSol == 1) {
			//printf("No twins, sorry\n");
			continue;
		}
		printf("%d solutions found\n", numSol);
		pencilmarks origPmAllowed(pm);
		origPmAllowed.fromSolver();
		//ms.solve(pm, &origSol, 1);
		//origSol.fromSolver();
		origSol.clear();
		origSol.fromSolver();
		origSol.allowSolution(sol);
		pencilmarks origSolAllowed(origSol);
		origSolAllowed.fromSolver();
		for(int n = 0; n < numSol; n++) {
			if(resPM[n] == origSolAllowed) continue; // one of the solutions is the original which we are not interested in
			pencilmarks ua(resPM[n]); // get new solution
			ua.clearBits(origSolAllowed); // clear cells that match old solution
			if(!ua.isSubsetOf(pm)) {
				// some new values aren't forbidden in the initial puzzle
				continue;
			}
			// start with initial puzzle
			pencilmarks res(pm);
			//res.toChars729(outPuz);
			//printf("%729.729s\tres1\n", outPuz);
			res |= origSolAllowed; // forbid original solution
			//res.toChars729(outPuz);
			//printf("%729.729s\tres2\n", outPuz);
			res.clearBits(resPM[n]); // allow the new solution
			//res &= resPM[n]; // allow the new solution
			//res.toChars729(outPuz);
			//printf("%729.729s\tres3\n", outPuz);
			for(int v = 0; v < 9; v++) {
				res[v].clearBits(emptyCells); // leave initially unresticted cells unrestricted
			}
			fsss2::hasSingleSolution ssTester;
			int newSol = ssTester.solve(res);
			if(newSol != 1) {
				pencilmarks allEmptyCells;
				for(int v = 0; v < 9; v++) {
					allEmptyCells[v] = emptyCells;
				}
				//printf("Oops, twin with %d solutions\n", newSol);
				pmInverse.toChars729(outPuz);
				printf("%729.729s\tInverted\n", outPuz);
				allEmptyCells.toChars729(outPuz);
				printf("%729.729s\tallEmptyCells\n", outPuz);
				origSol.toChars729(outPuz);
				printf("%729.729s\tOriginal solution\n", outPuz);
				pm.toChars729(outPuz);
				printf("%729.729s\tOriginal puzzle\n", outPuz);
				res.toChars729(outPuz);
				printf("%729.729s\tBad twin\n", outPuz);
				resPM[n].fromSolver();
				resPM[n].toChars729(outPuz);
				printf("%729.729s\tTwin solution\n", outPuz);
				exit(0);
				continue;
			}
			res.toChars729(outPuz);
			printf("%729.729s\tTwin\n", outPuz);
		}
	}
	delete[] resPM;
	return ret;
}

//#include <unistd.h> // sleep()
int transform::cmdClusterize() {
	struct cl {
		uint32_t label;
		uint32_t next_id;
	};
	int ret = 0;
	char line[2000];
	std::vector < pencilmarks > allPM;
	char outPuz[729];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		allPM.push_back(pm);
	}
	uint32_t numItems(allPM.size());
	//std::cout << numItems << " loaded" << std::endl;
	std::vector < cl > cl1(numItems);
	std::vector < cl > cl2(numItems);
	std::vector < cl > cl3(numItems);
	std::vector < cl > cl4(numItems);
//	std::vector < uint32_t > cl1(numItems);
//	std::vector < uint32_t > cl2(numItems);
//	std::vector < uint32_t > cl3(numItems);
//	std::vector < uint32_t > cl4(numItems);
//	std::vector < uint32_t > cl1n(numItems);
//	std::vector < uint32_t > cl2n(numItems);
//	std::vector < uint32_t > cl3n(numItems);
//	std::vector < uint32_t > cl4n(numItems);
	for(uint32_t first = 0; first < numItems; first++) {
		cl1[first] = {first,first};
		cl2[first] = {first,first};
		cl3[first] = {first,first};
		cl4[first] = {first,first};
//		cl1[first] = first;
//		cl2[first] = first;
//		cl3[first] = first;
//		cl4[first] = first;
//		cl1n[first] = first;
//		cl2n[first] = first;
//		cl3n[first] = first;
//		cl4n[first] = first;
	}
	//sleep(20);
	for(uint32_t first = 0; first < numItems; first++) {
		const pencilmarks& p1(allPM[first]);
		for(uint32_t second = first + 1; second < numItems; second++) {
			if(cl1[first].label == cl1[second].label) continue; // already in same partition
			pencilmarks p(allPM[second]);
			p ^= p1;
			int diff(p.popcount() / 2);
			uint32_t oldCluster;
			uint32_t newCluster;
			uint32_t oldIitem;
			switch (diff) {
				case 1:
					// at -+1
					oldCluster = std::max(cl1[first].label, cl1[second].label);
					newCluster = std::min(cl1[first].label, cl1[second].label);
					// update labels of old cluster to new cluster
					for(oldIitem = cl1[oldCluster].next_id; oldIitem != oldCluster; oldIitem = cl1[oldIitem].next_id) {
						cl1[oldIitem].label = newCluster;
					}
					cl1[oldIitem].label = newCluster;
					// insert oldCluster chain at top of newCluster chain
					std::swap(cl1[oldIitem].next_id, cl1[newCluster].next_id);
//					// update labels of old cluster to new cluster
//					for(oldIitem = cl1n[oldCluster]; oldIitem != oldCluster; oldIitem = cl1n[oldIitem]) {
//						cl1[oldIitem] = newCluster;
//					}
//					cl1[oldIitem] = newCluster;
//					// insert oldCluster chain at top of newCluster chain
//					std::swap(cl1n[oldIitem], cl1n[newCluster]);
					//if(newCluster != oldCluster) {
					//	for(uint32_t e = oldCluster; e < numItems; e++) {
					//		if(cl1[e] == oldCluster) cl1[e] = newCluster;
					//	}
					//}
					//break;
					[[fallthrough]];
				case 2:
					// at -+2
					oldCluster = std::max(cl2[first].label, cl2[second].label);
					newCluster = std::min(cl2[first].label, cl2[second].label);
					if(newCluster != oldCluster) {
						for(oldIitem = cl2[oldCluster].next_id; oldIitem != oldCluster; oldIitem = cl2[oldIitem].next_id) {
							cl2[oldIitem].label = newCluster;
						}
						cl2[oldIitem].label = newCluster;
						std::swap(cl2[oldIitem].next_id, cl2[newCluster].next_id);
					}
					//break;
					[[fallthrough]];
				case 3:
					// at -+3
					oldCluster = std::max(cl3[first].label, cl3[second].label);
					newCluster = std::min(cl3[first].label, cl3[second].label);
					if(newCluster != oldCluster) {
						for(oldIitem = cl3[oldCluster].next_id; oldIitem != oldCluster; oldIitem = cl3[oldIitem].next_id) {
							cl3[oldIitem].label = newCluster;
						}
						cl3[oldIitem].label = newCluster;
						std::swap(cl3[oldIitem].next_id, cl3[newCluster].next_id);
					}
					//break;
					[[fallthrough]];
				case 4:
					// at -+4
					oldCluster = std::max(cl4[first].label, cl4[second].label);
					newCluster = std::min(cl4[first].label, cl4[second].label);
					if(newCluster != oldCluster) {
						for(oldIitem = cl4[oldCluster].next_id; oldIitem != oldCluster; oldIitem = cl4[oldIitem].next_id) {
							cl4[oldIitem].label = newCluster;
						}
						cl4[oldIitem].label = newCluster;
						std::swap(cl4[oldIitem].next_id, cl4[newCluster].next_id);
					}
					break;
//				case 1:
//				case 3:
//				case 5:
//				case 7:
//					std::cout << diff << ",";
//					break;
				default:
					break;
			}
		}
	}
	for(uint32_t first = 0; first < numItems; first++) {
		allPM[first].toChars729(outPuz);
		printf("%729.729s\t%u\t%u\t%u\t%u\n", outPuz, cl1[first].label, cl2[first].label, cl3[first].label, cl4[first].label);
		//printf("%729.729s\t%u\t%u\t%u\n", outPuz, cl1[first].label, cl2[first].label, cl3[first].label);
	}
	return ret;
}
