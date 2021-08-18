/*
 * puzzleInvariants.h
 *
 *  Created on: Dec 13, 2020
 *      Author: mladen
 */

#ifndef PUZZLEINVARIANTS_H_
#define PUZZLEINVARIANTS_H_

#include "fsss2.h"

class puzzleInvariants {
	enum invariant {
		numConstraintsInCellMask = 1,
		numConstraintsForDigitMask = 2,
		numConstraintsInBoxMask = 4,
	};
	pencilmarks puzzle;
	uint64_t isProcessed = 0;
public:
	int numConstraintsInCell[81] = {0};
	int numConstraintsInBox[9] = {0};
	int numConstraintsForDigit[9] = {0};
	void countNumConstraintsInBox();
	void getBasicInvariants();
	puzzleInvariants(const pencilmarks& thePuzzle);
	virtual ~puzzleInvariants();
	void getBoxesWithMaxConstraints();
};

#endif /* PUZZLEINVARIANTS_H_ */
