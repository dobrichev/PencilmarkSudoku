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
	char line[2000];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		getSingleSolution ss;
		char sol[88];
		char outPuz[729];
		if(vanilla) {
			char p[81];
			for(int i = 0; i < 81; i++) p[i] = (line[i] <= '9' && line[i] > '0' ? line[i] - '0' : 0);
			if(1 != ss.solve(p, sol)) return 1;
		}
		else {
			if(!pm.fromChars729(line)) return 1;
			if(1 != ss.solve(pm, sol)) return 1;
		}
		pm.toChars729(outPuz);
		for(int i = 0; i < 81; i++) {
			sol[i] += '0';
		}
		printf("%729.729s\t%81.81s\n", outPuz, sol);
	}
	return 0;
}

