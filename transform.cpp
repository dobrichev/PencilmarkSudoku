#include "solRowMinLex.h"
#include "pencilmarks.h"
#include "options.h"
#include "fsss2.h"

int transform::cmdSolRowMinLex() {
	char line[2000];
	char outPuz[729];
	char sol[88];
	getAnySolution solver;
	bool vanilla = opt.getFlag("vanilla");
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(vanilla) {
			pm.fromChars81(line);
		}
		else {
			if(!pm.fromChars729(line)) return 1;
		}
		pencilmarks res;
		if(!solver.solve(pm, sol)) continue; //silently ignore invalid puzzles
		solRowMinLex::pmMinLex(pm, sol, res);
		res.toChars729(outPuz);
		printf("%729.729s\n", outPuz);
	}
	return 0;
}
