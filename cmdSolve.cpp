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
#include "templates.h"

int cmdSolve::exec() {
	bool minimals = opt.getFlag("minimals");
	bool count = opt.getFlag("count");
	bool vanilla = opt.getFlag("vanilla");
	int maxSolutionCount = opt.getIntValue("maxsolutioncount", INT_MAX);
	int ret = 0;
	char line[2000];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		fsss2::getSingleSolution ss;
		fsss2::multiSolutionPM ms;
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
		pm.toChars729(outPuz);
		if(count) {
			pencilmarks respm;
			char outPm[729];
			int numSol = ms.solve(pm, respm, maxSolutionCount);
			respm.fromSolver();
			respm.toChars729(outPm);
			printf("%729.729s\t%d\t%729.729s\n", outPuz, numSol, outPm);
		}
		else {
			//int numSol = templates::solve(pm, sol);
			int numSol = ss.solve(pm, sol);
			switch(numSol) {
				case 0:
					printf("%729.729s\tInvalid\n", outPuz);
					ret = 1;
					goto nextInput;
				case 2:
					printf("%729.729s\tMultiple\n", outPuz);
					ret = 1;
					goto nextInput;
			}
			for(int i = 0; i < 81; i++) {
				sol[i] += '0';
			}
			if(minimals) {
				int val = -1;
				int cell;
				getFirstRedundantConstraint(pm, val, cell);
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
		nextInput:;
	}
	return ret;
}
void cmdSolve::getFirstRedundantConstraint(const pencilmarks& forbiddenValuePositions, int& val, int& cell) {
	fsss2::hasSingleSolution sss;
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


