/*
 * puzzleInvariants.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: mladen
 */

#include "puzzleInvariants.h"
#include "tables.h"

puzzleInvariants::puzzleInvariants(const pencilmarks& thePuzzle) :
	puzzle(thePuzzle)
{
}

puzzleInvariants::~puzzleInvariants() {
	// TODO Auto-generated destructor stub
}

void puzzleInvariants::countNumConstraintsInBox() {
	if(isProcessed & invariant::numConstraintsInBoxMask) return;
	getBasicInvariants();
}
void puzzleInvariants::getBasicInvariants() {
	if(isProcessed & invariant::numConstraintsInCellMask) return;
	for(int d = 0; d < 9; d++) {
		numConstraintsForDigit[d] = puzzle[d].popcount_128();
		for(int c = 0; c < 81; c++) {
			if(puzzle[d].isBitSet(c)) {
				numConstraintsInCell[c]++;
				numConstraintsInBox[tables::affectedGroups[c][2] - 18]++;
			}
		}
	}
	isProcessed |= (invariant::numConstraintsForDigitMask | numConstraintsForDigitMask | numConstraintsInCellMask);
}

void puzzleInvariants::getBoxesWithMaxConstraints() {
}
