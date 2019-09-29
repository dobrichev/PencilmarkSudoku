/*
 * cmdSolve.h
 *
 *  Created on: Sep 29, 2019
  *      Author: Mladen Dobrichev
 */

#ifndef CMDSOLVE_H_
#define CMDSOLVE_H_

/*
 --solve             Solve puzzles
   --groupbygrid         Normalized puzzles grouped by solution
     --gridsonly             Prints ordered solution grids w/o duplicates
   --minimals            Check puzzles for minimality
   --count               Print only the solution count
     --maxsolutioncount <n>  Solves up to <n>-th solution (INT_MAX)
   --backdoor            Print backdoors size & exemplar
*/
class cmdSolve {
private:
	bool groupByGrid = false;
	bool gridsOnly = false;
	bool minimals = false;
	bool count = false;
	bool backdoor = false;
	bool vanilla = false;
	int maxSolutionCount = 0;
public:
	cmdSolve();
	int exec();
};

#endif /* CMDSOLVE_H_ */
