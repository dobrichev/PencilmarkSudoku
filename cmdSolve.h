/*
 * cmdSolve.h
 *
 *  Created on: Sep 29, 2019
  *      Author: Mladen Dobrichev
 */

#ifndef CMDSOLVE_H_
#define CMDSOLVE_H_

#include "pencilmarks.h"

/*
 --solve             Solve puzzles
   --vanilla             Input is vanilla 81-char puzzles (default is 729-char pencilmarks)
   --minimals            Check puzzles for minimality
   --count               Print only the solution count
     --maxsolutioncount <n>  Solves up to <n>-th solution (INT_MAX)
*/
class cmdSolve {
private:
public:
	int exec();
	static void getFirstRedundantConstraint(const pencilmarks& forbiddenValuePositions, int& val, int& cell);
};

#endif /* CMDSOLVE_H_ */
