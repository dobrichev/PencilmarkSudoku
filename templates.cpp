#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <algorithm>
#include "templates.h"
#include "fsss2.h"

bm128 templates::allTemplates[46656];
templateIndex templates::cellIndexes[81];
templateIndex templates::cellInverseIndexes[81];
templateIndex templates::disjointsIndexes[46656];
//templates globalTemplates;

templates::templates() {
	init();
}

unsigned long long templates::solve(const pencilmarks& forbiddenValuePositions, char* res) {
	struct digitMap_t {
		int digit;
		int size;
		bool operator<(const digitMap_t& other) {
			return (size < other.size);
		}
	};
	digitMap_t digitMap[9];
	templateIndex solTemplateIndexes[9];
	for(int d = 0; d < 9; d++) {
		solTemplateIndexes[d].setAll(); //all templates are potential candidates in forming the solution grid
		for(int c = 0; c < 81; c++) {
			if(forbiddenValuePositions[d].isBitSet(c)) {
				solTemplateIndexes[d].operator &=(templates::cellInverseIndexes[c]);
			}
		}
		digitMap[d].digit = d;
		digitMap[d].size = solTemplateIndexes[d].count();
//		//get union and intersection for the survived templates
//		bm128 u;
//		u.clear();
//		bm128 i = constraints::mask81;
//		for(int t = 0; t < 46656; t++) {
//			if(solTemplateIndexes[d][t]) {
//				u |= templates::allTemplates[t];
//				i &= templates::allTemplates[t];
//			}
//		}
//		printf("%d\t%d\t%d\t%d\n", d + 1, (int)solTemplateIndexes[d].count(), u.popcount_128(), i.popcount_128());
	}
//	for(int d = 0; d < 9; d++) {
//		for(int t = 0; t < 46656; t++) {
//			if(solTemplateIndexes[d][t]) {
//				for(int dd = 0; dd < 9; dd++) {
//					if(d == dd) continue;
//					for(int tt = 0; tt < 46656; tt++) {
//						if(solTemplateIndexes[dd][tt]) {
//							if(templates::allTemplates[t].isDisjoint(templates::allTemplates[tt])) {
//								goto nextDD;
//							}
//						}
//					}
//					//template [d][t] hasn't any disjoint template from [dd]
//					solTemplateIndexes[d].reset(t);
//					//printf("-");
//					goto nextT;
//					nextDD:
//					;
//				}
//			}
//			nextT:
//			;
//		}
//		printf("%d\t%d\n", d + 1, (int)solTemplateIndexes[d].count());
//	}
	std::sort(digitMap, digitMap + 9);
	for(int d = 0; d < 9; d++) {
		printf("%d\t%d\t%d\n", d, digitMap[d].digit + 1, digitMap[d].size);
	}
	for(int c = 0; c < 81; c++) {
		templateIndex tt = solTemplateIndexes[digitMap[0].digit];
		tt &= cellIndexes[c]; //assume c = digitMap[0].digit
		if(tt.any()) {
			//clear this cell from the rest of the digits
			templateIndex tt01 = solTemplateIndexes[digitMap[1].digit]; tt01 &= cellInverseIndexes[c];
			if(tt01.none()) continue;
			templateIndex tt02 = solTemplateIndexes[digitMap[2].digit]; tt02 &= cellInverseIndexes[c];
			if(tt02.none()) continue;
			templateIndex tt03 = solTemplateIndexes[digitMap[3].digit]; tt03 &= cellInverseIndexes[c];
			if(tt03.none()) continue;
			templateIndex tt04 = solTemplateIndexes[digitMap[4].digit]; tt04 &= cellInverseIndexes[c];
			if(tt04.none()) continue;
			templateIndex tt05 = solTemplateIndexes[digitMap[5].digit]; tt05 &= cellInverseIndexes[c];
			if(tt05.none()) continue;
			templateIndex tt06 = solTemplateIndexes[digitMap[6].digit]; tt06 &= cellInverseIndexes[c];
			if(tt06.none()) continue;
			templateIndex tt07 = solTemplateIndexes[digitMap[7].digit]; tt07 &= cellInverseIndexes[c];
			if(tt07.none()) continue;
			templateIndex tt08 = solTemplateIndexes[digitMap[8].digit]; tt08 &= cellInverseIndexes[c];
			if(tt08.none()) continue;
			for(size_t t0 = tt.first(); t0 < tt.size(); t0 = tt.next(t0)) {
				templateIndex t01 = tt01; t01 &= disjointsIndexes[t0];
				if(t01.none()) continue;
				templateIndex t02 = tt02; t02 &= disjointsIndexes[t0];
				if(t02.none()) continue;
				templateIndex t03 = tt03; t03 &= disjointsIndexes[t0];
				if(t03.none()) continue;
				templateIndex t04 = tt04; t04 &= disjointsIndexes[t0];
				if(t04.none()) continue;
				templateIndex t05 = tt05; t05 &= disjointsIndexes[t0];
				if(t05.none()) continue;
				templateIndex t06 = tt06; t06 &= disjointsIndexes[t0];
				if(t06.none()) continue;
				templateIndex t07 = tt07; t07 &= disjointsIndexes[t0];
				if(t07.none()) continue;
				templateIndex t08 = tt08; t08 &= disjointsIndexes[t0];
				if(t08.none()) continue;
				for(size_t t1 = t01.first(); t1 < t01.size(); t1 = t01.next(t1)) {
					templateIndex t12 = t02; t12 &= disjointsIndexes[t1];
					if(t12.none()) continue;
					templateIndex t13 = t03; t13 &= disjointsIndexes[t1];
					if(t13.none()) continue;
					templateIndex t14 = t04; t14 &= disjointsIndexes[t1];
					if(t14.none()) continue;
					templateIndex t15 = t05; t15 &= disjointsIndexes[t1];
					if(t15.none()) continue;
					templateIndex t16 = t06; t16 &= disjointsIndexes[t1];
					if(t16.none()) continue;
					templateIndex t17 = t07; t17 &= disjointsIndexes[t1];
					if(t17.none()) continue;
					templateIndex t18 = t08; t18 &= disjointsIndexes[t1];
					if(t18.none()) continue;
					for(size_t t2 = t12.first(); t2 < t12.size(); t2 = t12.next(t2)) {
						templateIndex t23 = t13; t23 &= disjointsIndexes[t2];
						if(t23.none()) continue;
						templateIndex t24 = t14; t24 &= disjointsIndexes[t2];
						if(t24.none()) continue;
						templateIndex t25 = t15; t25 &= disjointsIndexes[t2];
						if(t25.none()) continue;
						templateIndex t26 = t16; t26 &= disjointsIndexes[t2];
						if(t26.none()) continue;
						templateIndex t27 = t17; t27 &= disjointsIndexes[t2];
						if(t27.none()) continue;
						templateIndex t28 = t18; t28 &= disjointsIndexes[t2];
						if(t28.none()) continue;
						for(size_t t3 = t23.first(); t3 < t23.size(); t3 = t23.next(t3)) {
							templateIndex t34 = t24; t34 &= disjointsIndexes[t3];
							if(t34.none()) continue;
							templateIndex t35 = t25; t35 &= disjointsIndexes[t3];
							if(t35.none()) continue;
							templateIndex t36 = t26; t36 &= disjointsIndexes[t3];
							if(t36.none()) continue;
							templateIndex t37 = t27; t37 &= disjointsIndexes[t3];
							if(t37.none()) continue;
							templateIndex t38 = t28; t38 &= disjointsIndexes[t3];
							if(t38.none()) continue;
							for(size_t t4 = t34.first(); t4 < t34.size(); t4 = t34.next(t4)) {
								templateIndex t45 = t35; t45 &= disjointsIndexes[t4];
								if(t45.none()) continue;
								templateIndex t46 = t36; t46 &= disjointsIndexes[t4];
								if(t46.none()) continue;
								templateIndex t47 = t37; t47 &= disjointsIndexes[t4];
								if(t47.none()) continue;
								templateIndex t48 = t38; t48 &= disjointsIndexes[t4];
								if(t48.none()) continue;
								for(size_t t5 = t45.first(); t5 < t45.size(); t5 = t45.next(t5)) {
									templateIndex t56 = t46; t56 &= disjointsIndexes[t5];
									if(t56.none()) continue;
									templateIndex t57 = t47; t57 &= disjointsIndexes[t5];
									if(t57.none()) continue;
									templateIndex t58 = t48; t58 &= disjointsIndexes[t5];
									if(t58.none()) continue;
									for(size_t t6 = t56.first(); t6 < t56.size(); t6 = t56.next(t6)) {
										templateIndex t67 = t57; t67 &= disjointsIndexes[t6];
										if(t67.none()) continue;
										templateIndex t68 = t58; t68 &= disjointsIndexes[t6];
										if(t68.none()) continue;
										for(size_t t7 = t67.first(); t7 < t67.size(); t7 = t67.next(t7)) {
											templateIndex t78 = t68; t78 &= disjointsIndexes[t7];
											if(t78.none()) continue;
											for(size_t t8 = t78.first(); t8 < t78.size(); t8 = t78.next(t8)) {
												//at this point (t0,t1,..t8) form disjoint templates
												printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", (int)t0, (int)t1, (int)t2, (int)t3, (int)t4, (int)t5, (int)t6, (int)t7, (int)t8);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			solTemplateIndexes[digitMap[0].digit] &= cellInverseIndexes[c]; //clear from further tests
		}
	}

//	//nested loops
//	for(size_t t0 = solTemplateIndexes[digitMap[0].digit].first(); t0 < solTemplateIndexes[digitMap[0].digit].size(); t0 = solTemplateIndexes[digitMap[0].digit].next(t0)) {
//		templateIndex t01 = solTemplateIndexes[digitMap[1].digit]; t01 &= disjointsIndexes[t0];
//		if(t01.none()) continue;
//		templateIndex t02 = solTemplateIndexes[digitMap[2].digit]; t02 &= disjointsIndexes[t0];
//		if(t02.none()) continue;
//		templateIndex t03 = solTemplateIndexes[digitMap[3].digit]; t03 &= disjointsIndexes[t0];
//		if(t03.none()) continue;
//		templateIndex t04 = solTemplateIndexes[digitMap[4].digit]; t04 &= disjointsIndexes[t0];
//		if(t04.none()) continue;
//		templateIndex t05 = solTemplateIndexes[digitMap[5].digit]; t05 &= disjointsIndexes[t0];
//		if(t05.none()) continue;
//		templateIndex t06 = solTemplateIndexes[digitMap[6].digit]; t06 &= disjointsIndexes[t0];
//		if(t06.none()) continue;
//		templateIndex t07 = solTemplateIndexes[digitMap[7].digit]; t07 &= disjointsIndexes[t0];
//		if(t07.none()) continue;
//		templateIndex t08 = solTemplateIndexes[digitMap[8].digit]; t08 &= disjointsIndexes[t0];
//		if(t08.none()) continue;
//		//printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", (int)t01.count(), (int)t02.count(), (int)t03.count(), (int)t04.count(), (int)t05.count(), (int)t06.count(), (int)t07.count(), (int)t08.count());
//		//continue;
//		for(size_t t1 = t01.first(); t1 < t01.size(); t1 = t01.next(t1)) {
//			templateIndex t12 = t02; t12 &= disjointsIndexes[t1];
//			if(t12.none()) continue;
//			templateIndex t13 = t03; t13 &= disjointsIndexes[t1];
//			if(t13.none()) continue;
//			templateIndex t14 = t04; t14 &= disjointsIndexes[t1];
//			if(t14.none()) continue;
//			templateIndex t15 = t05; t15 &= disjointsIndexes[t1];
//			if(t15.none()) continue;
//			templateIndex t16 = t06; t16 &= disjointsIndexes[t1];
//			if(t16.none()) continue;
//			templateIndex t17 = t07; t17 &= disjointsIndexes[t1];
//			if(t17.none()) continue;
//			templateIndex t18 = t08; t18 &= disjointsIndexes[t1];
//			if(t18.none()) continue;
//			for(size_t t2 = t12.first(); t2 < t12.size(); t2 = t12.next(t2)) {
//				templateIndex t23 = t13; t23 &= disjointsIndexes[t2];
//				if(t23.none()) continue;
//				templateIndex t24 = t14; t24 &= disjointsIndexes[t2];
//				if(t24.none()) continue;
//				templateIndex t25 = t15; t25 &= disjointsIndexes[t2];
//				if(t25.none()) continue;
//				templateIndex t26 = t16; t26 &= disjointsIndexes[t2];
//				if(t26.none()) continue;
//				templateIndex t27 = t17; t27 &= disjointsIndexes[t2];
//				if(t27.none()) continue;
//				templateIndex t28 = t18; t28 &= disjointsIndexes[t2];
//				if(t28.none()) continue;
//				for(size_t t3 = t23.first(); t3 < t23.size(); t3 = t23.next(t3)) {
//					templateIndex t34 = t24; t34 &= disjointsIndexes[t3];
//					if(t34.none()) continue;
//					templateIndex t35 = t25; t35 &= disjointsIndexes[t3];
//					if(t35.none()) continue;
//					templateIndex t36 = t26; t36 &= disjointsIndexes[t3];
//					if(t36.none()) continue;
//					templateIndex t37 = t27; t37 &= disjointsIndexes[t3];
//					if(t37.none()) continue;
//					templateIndex t38 = t28; t38 &= disjointsIndexes[t3];
//					if(t38.none()) continue;
//					for(size_t t4 = t34.first(); t4 < t34.size(); t4 = t34.next(t4)) {
//						templateIndex t45 = t35; t45 &= disjointsIndexes[t4];
//						if(t45.none()) continue;
//						templateIndex t46 = t36; t46 &= disjointsIndexes[t4];
//						if(t46.none()) continue;
//						templateIndex t47 = t37; t47 &= disjointsIndexes[t4];
//						if(t47.none()) continue;
//						templateIndex t48 = t38; t48 &= disjointsIndexes[t4];
//						if(t48.none()) continue;
//						for(size_t t5 = t45.first(); t5 < t45.size(); t5 = t45.next(t5)) {
//							templateIndex t56 = t46; t56 &= disjointsIndexes[t5];
//							if(t56.none()) continue;
//							templateIndex t57 = t47; t57 &= disjointsIndexes[t5];
//							if(t57.none()) continue;
//							templateIndex t58 = t48; t58 &= disjointsIndexes[t5];
//							if(t58.none()) continue;
//							for(size_t t6 = t56.first(); t6 < t56.size(); t6 = t56.next(t6)) {
//								templateIndex t67 = t57; t67 &= disjointsIndexes[t6];
//								if(t67.none()) continue;
//								templateIndex t68 = t58; t68 &= disjointsIndexes[t6];
//								if(t68.none()) continue;
//								for(size_t t7 = t67.first(); t7 < t67.size(); t7 = t67.next(t7)) {
//									templateIndex t78 = t68; t78 &= disjointsIndexes[t7];
//									if(t78.none()) continue;
//									for(size_t t8 = t78.first(); t8 < t78.size(); t8 = t78.next(t8)) {
//										//at this point (t0,t1,..t8) form disjoint templates
//										printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", (int)t0, (int)t1, (int)t2, (int)t3, (int)t4, (int)t5, (int)t6, (int)t7, (int)t8);
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
	return 0;
}

//unsigned long long templates::nSol(const char *p) {
//	//~80 puzzles/second for Gordon Royle's list of 17s (500/s initialization only), 400/s w/o guessing
//	bm128 clues[9]; //positions of the givens for each digit
//	bm128 invalid[9]; //forbidden positions for each digit
//
////Take a puzzle. Example from Patterns Game.
////... ..1 ..2
////..3 .4. .5.
////.6. 7. .8..
////
////..6 ... .7.
////.4. .2. ..3
////1.. ..4 9..
////
////..8 ..9 5..
////.7. 8.. .6.
////6.. .5. ... ER=6.6/6.6/6.6 - joel64, patterns game 146
////
////Step A. Prepare 9 81-bit masks, one per digit. Example for digit 7.
////.*. *** .*2
////.*3 *** .*.
////*** 7** ***
////
////*** *** *7*
////.*. *2. ***
////1*. *.4 ***
////
////*** *.9 5*.
////*7* *** ***
////*** *5. .*. Digit 7 step A1: set all visible cells
////
////
////.*. *** .**
////.** *** .*.
////*** 7** ***
////
////*** *** *7*
////.*. **. ***
////**. *.* ***
////
////*** *.* **.
////*7* *** ***
////*** **. .*. Digit 7 step A2: set all givens <> 7
////
////
////.*. *** .**
////.** *** .*.
////*** .** ***
////
////*** *** *.*
////.*. **. ***
////**. *.* ***
////
////*** *.* **.
////*.* *** ***
////*** **. .*. Digit 7 mask: only 6 from the 46656 possible templates are disjoint to this mask
////
////Step B. Apply the 9 masks over all 46656 templates. Store all disjoint to the mask templates as candidates for the respective digit.
////
////Template distribution 36 28 54 28 14  4  6 14 42 	product=301112598528 sum=226
////
////Step C. Perform some basic eliminations (none of them is required for this example puzzle).
////
////Step D. Remove all templates that have no at least one disjoint template for each of the other digits.
////Repeat until solution found or no more eliminations exist.
////
////Template distribution  1  1  1  1  1  1  1  1  1 	product=1            sum=9 (example puzzle solved)
////
////Steps E-Y. Still unknown.
////
////Step Z. Last resort: Reorder digits (relabel) in accending order by number of templates, perform 9 nested loops, find all disjoint templates.
////
////No-solution condition: A digit with 0 template candidates.
////Single-solution condition: 9 disjoint templates remain, one for each digit.
////Multiple-solution condition: More than one possibility to form 9 disjoint templates, one for each digit.
////
////The basic methods include:
////- Solve a cell if only templates for one of the digits hit it. Remove the templates for the same digit that not hit the solved cell.
////- Solve a digit if there is a cell covered by only one template. Remove rest of the templates for this digit. Remove the templates for other digits that hit the solved digit.
////- Other methods, suggested (not yet) by experts.
////
////Step B rate is ~500 puzzles/sec.
////Generating large amount of solutions for multiple-solution puzzle is expected to be fairly fast.
//
//	bm128 allClues; //all givens
//	unsigned short invalids[46656]; //bit (d - 1) is set if the respective template is forbidden for digit d.
//	int kTemplCount[9];
//	int validCount[9]; //how many valid templates remain for each digit
//	unsigned long long ret = 0;
//	//ch81 prBuf; //print buffer for debugging/explaining
//#ifdef __INTEL_COMPILER
//#pragma noparallel
//#endif //__INTEL_COMPILER
//	for(int t = 0; t < 46656; t++)
//		invalids[t] = 0; //initially there are no invalid templates
//	for(int d = 0; d < 9; d++) {
//		clues[d].clear(); //initially there are no clues
//		validCount[d] = 46656; //initially every digit has 46656 valid templates
//		invalid[d].clear(); //initially all digits have no invalid positions
//		kTemplCount[d] = 0;
//	}
//	allClues.clear();
//	for(int c = 0; c < 81; c++) {
//		int d = p[c];
//		if(d--) { //work with zero based digits 0..8
//			clues[d].setBit(c); //cell c is given for digit d
//			allClues.setBit(c); //cell c is given
//			for(int r = 0; r < 20; r++) { //all templates visible from the given are invalid
//				invalid[d].setBit(affectedCells[c][r]); //related cell r can't contain the same digit d
//			}
//		}
//	}
//	for(int d = 0; d < 9; d++) {
//		bm128 rest; //all givens but d
//		rest = allClues;
//		rest ^= clues[d];
//		invalid[d] |= rest; //d can't share cells with other givens
//	}
//	//the only one missing bit in the houses of the givens in invalid[] guaranees also the existence of the givens
//	for(int t = 0; t < 46656; t++) {
//		for(int d = 0; d < 9; d++) {
//			bm128 tt = allTemplates[t];
//			tt &= invalid[d]; //find forbidden positions for digit d in template t
//			if(!tt.isZero()) { //invalid template for this digit
//				invalids[t] |= Digit2Bitmap[d + 1]; //mark the respective bit
//				validCount[d]--; //one less template candidate
//			}
//		}
//	}
//
//	//for(int c = 0; c < 81; c++) {
//	//	printf("%c", p[c] + '0');
//	//}
//	//printf("\n");
//
//	int tCount = 0; //all template candidates
//	int tCounts[9]; //template candidates per digit
//	int solvedDigits = 0;
//	unsigned long long rating = 1;
//	for(int d = 0; d < 9; d++) {
//		tCount += validCount[d];
//		tCounts[d] = 0;
//		printf("%d ", validCount[d]);
//		rating *= validCount[d];
//		if(validCount[d] == 1)
//			solvedDigits |= Digit2Bitmap[d + 1];
//	}
//	printf("\t%llu (pass 1) tCount = %d\n", rating, tCount);
//
//	bm128 **digitTemplates[9]; //9 pointers to arrays of the valid templates
//	digitTemplates[0] = (bm128**)malloc(tCount * sizeof(bm128*));
//	for(int d = 0; d < 9 - 1; d++) {
//		digitTemplates[d + 1] = digitTemplates[d] + validCount[d];
//	}
//
//	//obtain pointers to the valid templates
//	for(int t = 0; t < 46656; t++) {
//		if(511 == (invalids[t] & 511))
//			continue; //nothing to do with entirely invalid template
//		for(int d = 0; d < 9; d++) {
//			if(0 == (invalids[t] & Digit2Bitmap[d + 1])) {
//				digitTemplates[d][tCounts[d]++] = &allTemplates[t];
//			}
//		}
//	}
//
//
//	bool repeat;
//	do {
//restart:
//
//		//printf("\nSurvived templates\n");
//		//for(int d = 0; d < 9; d++) {
//		//	for(int t = 0; t < validCount[d]; t++) {
//		//		digitTemplates[d][t]->toMask81('1' + d, prBuf.chars);
//		//		printf("%81.81s\t%d\n", prBuf.chars, t + 1);
//		//	}
//		//}
//
//		repeat = false;
//		//fix the templates which are the only candidate for a cell
//		bm128 allPoss;
//		allPoss.clear();
//		bm128 duplicates;
//		duplicates.clear();
//		for(int d = 0; d < 9; d++) {
//			bm128 newSolvedCells;
//			newSolvedCells -= clues[d]; //all cells except givens are candidates for digit d
//			for(int t = 0; t < validCount[d]; t++) {
//				duplicates |= (allPoss & *digitTemplates[d][t]);
//				allPoss |= *digitTemplates[d][t];
//				newSolvedCells &= *digitTemplates[d][t]; //d is not in this cell for at least one template, leave cell unsolved.
//			}
//			//add to newly solved cells these having this digit as only candidate
//			bm128 allDigitPoss = maskLSB[81].m128i_m128i; //all cells are candidates for digit 2
//			for(int d2 = 0; d2 < 9; d2++) {
//				if(d2 == d)
//					continue;
//				for(int t2 = 0; t2 < validCount[d2]; t2++) {
//					allDigitPoss.clearBits(*digitTemplates[d2][t2]); //exclude cells where at least one <> d candidate exists
//				}
//			}
//			allDigitPoss.clearBits(clues[d]); //remove also previously known givens
//			if(!allDigitPoss.isZero()) {
//				int firstRemoved = -1;
//				for(int t = 0; t < validCount[d]; t++) {
//					bm128 notSolvedCell = allDigitPoss;
//					notSolvedCell.clearBits(*digitTemplates[d][t]);
//					if(!notSolvedCell.isZero()) {
//						//a candidate template with missing solved cell is invalid
//						digitTemplates[d][t] = NULL;
//						if(firstRemoved == -1) {
//							firstRemoved = t;
//						}
//					}
//				}
//				if(firstRemoved != -1) {
//					//cleanup the NULL template pointers
//					int t2 = firstRemoved;
//					for(int t1 = firstRemoved + 1; t1 < validCount[d]; t1++) {
//						if(digitTemplates[d][t1])
//							digitTemplates[d][t2++] = digitTemplates[d][t1];
//					}
//					validCount[d] = t2;
//					repeat = true; //perform next pass
//					if(t2 == 0) {
//						printf("No valid template for digit %d.\n", d + 1); //no solution
//						goto exit;
//					}
//					if(t2 == 1) {
//						clues[d] = *digitTemplates[d][0];; //solved digit
//						solvedDigits |= Digit2Bitmap[d + 1];
//					}
//					goto restart; //???
//				}
//				newSolvedCells |= allDigitPoss;
//			}
//			//eliminate contradicting templates from other digits for newly solved cells
//			if(!newSolvedCells.isZero()) {
//				clues[d] |= newSolvedCells;
//				for(int d2 = 0; d2 < 9; d2++) {
//					if(d2 == d)
//						continue;
//					int firstRemoved = -1;
//					for(int t2 = 0; t2 < validCount[d2]; t2++) {
//						if(!newSolvedCells.isDisjoint(*digitTemplates[d2][t2])) {
//							//remove this template from the list
//							digitTemplates[d2][t2] = NULL;
//							if(firstRemoved == -1)
//								firstRemoved = t2;
//						}
//					}
//					if(firstRemoved != -1) {
//						//cleanup the NULL template pointers
//						int t2 = firstRemoved;
//						for(int t1 = firstRemoved + 1; t1 < validCount[d2]; t1++) {
//							if(digitTemplates[d2][t1])
//								digitTemplates[d2][t2++] = digitTemplates[d2][t1];
//						}
//						validCount[d2] = t2;
//						repeat = true; //perform next pass
//						if(t2 == 0) {
//							printf("No valid template for digit %d.\n", d2 + 1); //no solution
//							goto exit;
//						}
//						if(t2 == 1) {
//							clues[d2] = *digitTemplates[d2][0];; //solved digit
//							solvedDigits |= Digit2Bitmap[d2 + 1];
//						}
//						//goto restart; //20% slower
//					}
//				}
//				goto restart; //1% slower
//			}
//		}
//		bm128 uniques = allPoss;
//		uniques ^= duplicates;
//		for(int d = 0; d < 9 && (!uniques.isZero()); d++) { //exit the loop when uniques exhausted
//			if(validCount[d] == 1) {
//				//it is OK a solved digit to occur once in all template candidates
//				uniques.clearBits(*digitTemplates[d][0]); //cleanup uniques
//				continue;
//			}
//			for(int t = 0; t < validCount[d]; t++) {
//				if(!digitTemplates[d][t]->isDisjoint(uniques)) {
//					validCount[d] = 1; //solve this digit
//					solvedDigits |= Digit2Bitmap[d + 1];
//					digitTemplates[d][0] = digitTemplates[d][t]; //assign pointer
//					clues[d] = *digitTemplates[d][0];
//					uniques.clearBits(*digitTemplates[d][0]); //cleanup uniques
//					repeat = true;
//					//goto restart; //1.3% faster for newSolvedCells disabled
//				}
//			}
//		}
//		if(repeat && solvedDigits != 511)
//			goto restart;
//
//		//filter out templates which haven't at least one disjoint template for each of the rest digits
//		tCount = 0;
//		for(int d1 = 0; d1 < 9; d1++) {
//			int firstRemoved = -1;
//			for(int t1 = 0; t1 < validCount[d1]; t1++) {
//				//find at least one disjoint template from the rest digits
//				int conflict;
//				for(int d2 = 0; d2 < 9; d2++) {
//					if(d1 == d2)
//						continue;
//					conflict = 1;
//					for(int t2 = 0; t2 < validCount[d2]; t2++) {
//						if(digitTemplates[d1][t1]->isDisjoint(*digitTemplates[d2][t2])) {
//							conflict = 0;
//							break; //stop at first found
//						}
//					}
//					if(conflict) { //invalid template [d1][t1]
//						//remove this template from the list
//						printf("\nElimination of template %d for digit %d due to conflict with each of the templates for digit %d.\n", t1 + 1, d1 + 1, d2 + 1); //no solution
//						digitTemplates[d1][t1] = NULL;
//						if(firstRemoved == -1)
//							firstRemoved = t1;
//						break;
//					}
//				}
//			}
//			if(firstRemoved != -1) {
//				//cleanup the NULL template pointers
//				int t2 = firstRemoved;
//				for(int t1 = firstRemoved + 1; t1 < validCount[d1]; t1++) {
//					if(digitTemplates[d1][t1])
//						digitTemplates[d1][t2++] = digitTemplates[d1][t1];
//				}
//				validCount[d1] = t2;
//				repeat = true; //perform next pass
//				if(t2 == 0) {
//					printf("No valid template for digit %d.\n", d1 + 1); //no solution
//					goto exit;
//				}
//				if(t2 == 1) {
//					clues[d1] = *digitTemplates[d1][0];; //solved digit
//					solvedDigits |= Digit2Bitmap[d1 + 1];
//				}
//				//goto restart; //~8% slower
//			}
//		}
//		rating = 1;
//		tCount = 0;
//		for(int d = 0; d < 9; d++) {
//			printf("%d ", validCount[d]);
//			rating *= validCount[d];
//			tCount += validCount[d];
//		}
//		printf("\t%llu (pass 2) tCount = %d\n", rating, tCount);
//	} while(repeat && (solvedDigits != 511)); //some template removed and the rest of the templates are still not unique
//
//	rating = 1;
//	tCount = 0;
//	for(int d = 0; d < 9; d++) {
//		printf("%d\t", validCount[d]);
//		rating *= validCount[d];
//		tCount += validCount[d];
//	}
//	printf("%d\t%llu\n", tCount, rating);
//
//	//if(tCount > 9) ret = 2; else ret = 1; goto exit;
//
//	if(tCount > 9) {
//		//find 9 disjoint templates
//		kTemplCount[0] = validCount[0];
//		for(int t1 = 0; t1 < validCount[0]; t1++) {
//			for(int t2 = 0; t2 < validCount[1]; t2++) {
//				bm128 t12 = *digitTemplates[0][t1];
//				if(!digitTemplates[1][t2]->isDisjoint(t12))
//					continue;
//				kTemplCount[1]++;
//				t12 |= *digitTemplates[1][t2];
//				for(int t3 = 0; t3 < validCount[2]; t3++) {
//					if(!digitTemplates[2][t3]->isDisjoint(t12))
//						continue;
//					kTemplCount[2]++;
//					bm128 t123 = t12;
//					t123 |= *digitTemplates[2][t3];
//					for(int t4 = 0; t4 < validCount[3]; t4++) {
//						if(!digitTemplates[3][t4]->isDisjoint(t123))
//							continue;
//						kTemplCount[3]++;
//						bm128 t1234 = t123;
//						t1234 |= *digitTemplates[3][t4];
//						for(int t5 = 0; t5 < validCount[4]; t5++) {
//							if(!digitTemplates[4][t5]->isDisjoint(t1234))
//								continue;
//							kTemplCount[4]++;
//							bm128 t12345 = t1234;
//							t12345 |= *digitTemplates[4][t5];
//							for(int t6 = 0; t6 < validCount[5]; t6++) {
//								if(!digitTemplates[5][t6]->isDisjoint(t12345))
//									continue;
//								kTemplCount[5]++;
//								bm128 t123456 = t12345;
//								t123456 |= *digitTemplates[5][t6];
//								for(int t7 = 0; t7 < validCount[6]; t7++) {
//									if(!digitTemplates[6][t7]->isDisjoint(t123456))
//										continue;
//									kTemplCount[6]++;
//									bm128 t1234567 = t123456;
//									t1234567 |= *digitTemplates[6][t7];
//									for(int t8 = 0; t8 < validCount[7]; t8++) {
//										if(!digitTemplates[7][t8]->isDisjoint(t1234567))
//											continue;
//										kTemplCount[7]++;
//										bm128 t12345678 = t1234567;
//										t12345678 |= *digitTemplates[7][t8];
//										for(int t9 = 0; t9 < validCount[8]; t9++) {
//											if(!digitTemplates[8][t9]->isDisjoint(t12345678))
//												continue;
//											kTemplCount[8]++;
//											ret++;
//											//bm128 t123456789 = t12345678;
//											//t123456789 |= *digitTemplates[8][t9];
//											if(ret % 10000 == 0) {
//												printf("Sol: %llu", ret);
//												for(int d = 0; d < 8; d++) {
//													printf("\t%d", kTemplCount[d]); //kTemplCount[8] is the number of solutions
//												}
//												printf("\n");
//											}
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//		for(int d = 0; d < 9; d++) {
//			printf("%d ", kTemplCount[d]); //kTemplCount[8] is the number of solutions
//		}
//		printf("\t(pass 3) tCount=%d\n", tCount);
//	}
//exit:
//	free(digitTemplates[0]);
//	return ret;
//}

void templates::init() {
	int nTemplates = 0;
	for(int r1c = 0; r1c < 9; r1c++) { //row 1 columns
		int r1box = r1c / 3;
		//int nColTemplates = 0;
		for(int r2c = 0; r2c < 9; r2c++) {
			int r2box = r2c / 3;
			if(r2box == r1box)
				continue;
			for(int r3c = 0; r3c < 9; r3c++) {
				int r3box = r3c / 3;
				if(r3box == r1box || r3box == r2box)
					continue;
				for(int r4c = 0; r4c < 9; r4c++) {
					int r4box = r4c / 3;
					if(r4c == r1c || r4c == r2c || r4c == r3c)
						continue;
					for(int r5c = 0; r5c < 9; r5c++) {
						int r5box = r5c / 3;
						if(r5box == r4box || r5c == r1c || r5c == r2c || r5c == r3c)
							continue;
						for(int r6c = 0; r6c < 9; r6c++) {
							int r6box = r6c / 3;
							if(r6box == r4box || r6box == r5box || r6c == r1c || r6c == r2c || r6c == r3c)
								continue;
							for(int r7c = 0; r7c < 9; r7c++) {
								int r7box = r7c / 3;
								if(r7c == r1c || r7c == r2c || r7c == r3c || r7c == r4c || r7c == r5c || r7c == r6c)
									continue;
								for(int r8c = 0; r8c < 9; r8c++) {
									int r8box = r8c / 3;
									if(r8box == r7box || r8c == r1c || r8c == r2c || r8c == r3c || r8c == r4c || r8c == r5c || r8c == r6c)
										continue;
									for(int r9c = 0; r9c < 9; r9c++) {
										int r9box = r9c / 3;
										if(r9box == r7box || r9box == r8box || r9c == r1c || r9c == r2c || r9c == r3c || r9c == r4c || r9c == r5c || r9c == r6c)
											continue;
										//this combination of r1c..r9c conforms Sudoku rules for valid locations of a single digit
										bm128& t = templates::allTemplates[nTemplates];
										t.clear();
										t.setBit(r1c);
										cellIndexes[r1c].set(nTemplates);
										t.setBit(9 + r2c);
										cellIndexes[9 + r2c].set(nTemplates);
										t.setBit(18 + r3c);
										cellIndexes[18 + r3c].set(nTemplates);
										t.setBit(27 + r4c);
										cellIndexes[27 + r4c].set(nTemplates);
										t.setBit(36 + r5c);
										cellIndexes[36 + r5c].set(nTemplates);
										t.setBit(45 + r6c);
										cellIndexes[45 + r6c].set(nTemplates);
										t.setBit(54 + r7c);
										cellIndexes[54 + r7c].set(nTemplates);
										t.setBit(63 + r8c);
										cellIndexes[63 + r8c].set(nTemplates);
										t.setBit(72 + r9c);
										cellIndexes[72 + r9c].set(nTemplates);
										nTemplates++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for(int i = 0; i < 81; i++) {
		cellInverseIndexes[i].setInverseOf(cellIndexes[i]);
	}
	for(int i = 0; i < 46656; i++) {
		for(int j = 0; j < 46656; j++) {
			if(allTemplates[i].isDisjoint(allTemplates[j])) {
				disjointsIndexes[i].set(j);
			}
		}
	}
//	for(int i = 0; i < 9; i++) {
//		colTemplatesIndexAll[i] = colTemplates_index_type(colTemplates[i], 5184, colTemplatesIndexes[i]); //build colTemplatesIndexes
//	}
}

/*
void countSolutions () {
	templates x;
	char buf[1000];
	while(fgets(buf, sizeof(buf), stdin)) {
		ch81 puz;
		puz.fromString(buf);
		printf("%s", buf);
		x.nSol(puz.chars);
	}

	//for(int i = 0; i < 81; i++) {
	//	//p[i] = "100000009000000020780030000000005300010200040000000000040900000000010800002000005"[i] - '0'; //17 1 71 103 62 6000 745 121 90 375,207,565,926,600,000 easy (no guesses)
	//	//p[i] = "100000009000000000780030000000005300010200040000000000040900000000010800002000005"[i] - '0'; //multiple solutions
	//	//p[i] = "100000002090400050006000700050903000000070000000850040700000600030009080002000001"[i] - '0'; //41 39 130 32 18 41 8 148 18 104,621,842,391,040 Easter Monster gd=8
	//	//p[i] = "000000039000001005003050800008090006070002000100400000009080050020000600400700000"[i] - '0'; //47 37 108 38 32 96 52 12 16 218,893,425,573,888 Golden Nugget gd=8
	//	//p[i] = "000000012000000003002300400001800005060070800000009000008500000900040500470006000"[i] - '0'; //65 111 109 34 12 50 73 24 47 Platinium Blonde
	//	//p[i] = "000000007020400060100000500090002040000800600600900000005003000030080020700004001"[i] - '0'; //42 10 113 24 42 28 57 144 88 Tungston Rod
	//	//p[i] = "000000003001005600090040070000009050700000008050402000080020090003500100600000000"[i] - '0'; //34 150 66 154 9 68 66 65 7 Fata Morgana
	//	//p[i] = "100000007020400060003000500090040000000062040000900800005000003060200080700001000"[i] - '0'; //34 22 36 18 44 16 43 92 116 156,589,823,655,936 Silver Plate gd=10
	//	//p[i] = "000100203000402000000035001670000480003000600048000039700850000050206000806009000"[i] - '0'; //34 17 4 12 22 8 62 7 80 9.9/9.9/2.6
	//	//p[i] = "000000002001002700030040050004905060000060000060403500090030040007800100800000000"[i] - '0'; //32 38 15 6 53 49 60 38 132 11.4/11.4/10.8
	//	//p[i] = "900000800070060000005004003000003500040090020006100004200500000000080070001006005"[i] - '0'; //61 44 61 20 5 20 25 44 46 11.3/11.3/10.4 champagne
	//	//game 146
	//	//p[i] = "000009002003050080060800400005000020090060001100004900007005200080100070300070000"[i] - '0'; //14 24 60 41 13 33 32 10 18 10.8/10.8/10.1 champagne
	//	//p[i] = "000002004003050070090600200006000010070040008500009700001008500060700080800010000"[i] - '0'; //14 80 281 28 9 10 6 10 49 10.7/10.7/10.6 champagne
	//	//p[i] = "000007004008090060030100900009000050060080007400001600005004200010200030200010000"[i] - '0'; //8 24 29 5 48 43 40 33 23 9.9/9.9/9.9 ronk
	//	//p[i] = "000001004003070080060500700005000030070090001800004600009003200050600090200080000"[i] - '0'; //40 64 5 28 10 5 23 8 17 9.8/9.8/9.8 champagne
	//	//p[i] = "000001002003040050060700800009000010010020003800003400002005600070200090400070000"[i] - '0'; //23 5 14 8 82 35 16 46 36 9.7/9.7/9.7 joel64
	//	//p[i] = "000008004009050030070100500005000070030080002100006300004005200080600090600010000"[i] - '0'; //10 80 43 54 5 10 48 14 29 9.6/9.6/9.6 champagne
	//	//p[i] = "000001002003040050060700400004000070050080001200007800008002900010900060900070000"[i] - '0'; //8 5 281 23 66 29 12 20 24 2,850,089,932,800 9.5/9.5/9.5 m_b_metcalf
	//	//p[i] = "000001002003040050060700800007000010010020008900005400005004600080500070200060000"[i] - '0'; //6.7/6.7/6.7 - joel64
	//	p[i] = "000001002003040050060700800006000070040020003100004900008009500070800060600050000"[i] - '0'; //6.6/6.6/6.6 - joel64 (no guesses)
	//	//p[i] = "000001004003050070060700900005000060070040002800002400009005200050600010100080000"[i] - '0'; //6.5/3.0/3.0 - champagne
	//	//p[i] = "000009004001060090020300600008000070090040008700006500004003200010200030200010000"[i] - '0'; //6.2/6.2/6.2 + ronk
	//	//p[i] = "000002007005060090070400800009000060010080005700003400006005100040200030200010000"[i] - '0'; //4.4/4.4/4.4 - ronk
	//	//p[i] = "000008009009060080020300600004000090080070004700006100005003200040200030200010000"[i] - '0'; //4.2/4.2/4.2 - ronk
	//	//p[i] = "000009005004060010070400300008000090020050008700006500003004100040300020200010000"[i] - '0'; //4.0/4.0/4.0 - ronk
	//	//p[i] = "000001002003040050060700800009000010010020003600004200008003500070800090900050000"[i] - '0'; //3.6/3.6/3.6 - joel64
	//	//p[i] = "000001002003040050060700800009000010010030009300004600008006500020800070900050000"[i] - '0'; //3.4/3.4/3.4 - joel64
	//	//p[i] = "000003009006070050050200800009000080080020007100007600005002400010400030200010000"[i] - '0'; //3.2/3.2/3.2 - ronk
	//	//p[i] = "000001005008090020020300800005000090030040006800007400007006500050400030200010000"[i] - '0'; //3.0/3.0/3.0 - ronk
	//	//p[i] = "000001002003040010040500600007000030010070008900002500004007800020400060800060000"[i] - '0'; //2.8/2.8/2.8 - joel64
	//	//p[i] = "000006001002070090010200300005000060090080005800004700006002400050400030200010000"[i] - '0'; //2.5/2.5/2.5 - ronk
	//	//p[i] = "000001002003040010040500600007000030080050004900002500002007800090300060800060000"[i] - '0'; //2.0/2.0/2.0 - joel64
	//	//p[i] = "000001002003040050050600100007000040060020008400006300006003800040900010900060000"[i] - '0'; //1.5/1.5/1.5 + m_b_metcalf (no guesses)
	//	//p[i] = "000008004003060080060700100005000030030080006100004700006005200040300010200010000"[i] - '0'; //1.2/1.2/1.2 - ronk (no guesses)
	//}
	//nSol(p);
}
*/
