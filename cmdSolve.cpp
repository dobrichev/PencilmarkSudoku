/*
 * cmdSolve.cpp
 *
 *  Created on: Sep 29, 2019
 *      Author: Mladen Dobrichev
 */

#include <iostream>
#include "cmdSolve.h"
#include "options.h"
#include "fsss2.h"

cmdSolve::cmdSolve() {
	groupByGrid = opt.getFlag("groupbygrid");
	gridsOnly = opt.getFlag("gridsonly");
	minimals = opt.getFlag("minimals");
	count = opt.getFlag("count");
	backdoor = opt.getFlag("backdoor");
	vanilla = opt.getFlag("vanilla");
	maxSolutionCount = opt.getIntValue("maxsolutioncount", INT_MAX);
}
int cmdSolve::exec() {
	int ret = 0;
	char line[2000];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		getSingleSolution ss;
		char sol[88];
		char outPuz[729];
		if(vanilla) {
			pm.fromChars81(line);
		}
		else {
			if(!pm.fromChars729(line)) {
				ret = 1;
				continue;
			}
		}
		if(1 != ss.solve(pm, sol)) {
			ret = 1;
			continue;
		}
		pm.toChars729(outPuz);
		for(int i = 0; i < 81; i++) {
			sol[i] += '0';
		}
		if(minimals) {
			int val = -1;
			int cell;
			getFirstRedundantConstraint(sol, pm, val, cell);
			if(val == -1) {
				printf("%729.729s\t%81.81s\tMinimal\n", outPuz, sol);
			}
			else {
				printf("%729.729s\t%81.81s\tRedundant(val=%d,pos=%d)\n", outPuz, sol, val, cell);
			}
		}
		else {
			printf("%729.729s\t%81.81s\n", outPuz, sol);
		}
	}
	return ret;
}
void cmdSolve::getFirstRedundantConstraint(const char* sol, const pencilmarks& forbiddenValuePositions, int& val, int& cell) {
	hasSingleSolution sss;
	for(int d = 0; d < 9; d++) {
		for(int c = 0; c < 81; c++) {
			if(forbiddenValuePositions[d].isBitSet(c)) {
				//try removal of this pencilmark and see whether it causes 2+ solutions
				pencilmarks m1(forbiddenValuePositions);
				m1[d].clearBit(c);
				if(2 != sss.solve(m1)) {
					val = d + 1;
					cell = c;
					return;
				}
			}
		}
	}
}


