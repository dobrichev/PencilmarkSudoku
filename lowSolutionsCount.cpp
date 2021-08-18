/*
 * lowSolutionsCount.cpp
 *
 *  Created on: Dec 12, 2020
 *      Author: mladen
 */

#include <stdio.h>
#include <iostream>
#include <map>
#include "lowSolutionsCount.h"
#include "options.h"
#include "puzzleInvariants.h"
#include "solRowMinLex.h"

template<typename SourceContainerType, typename DestContainerType>
void getXua(const pencilmarks& base, const SourceContainerType& src, DestContainerType& res) {
	res.clear();
	for(auto&& s : src) {
		pencilmarks ua(s);
		ua.clearBits(base);
		if(ua.isZero()) continue; //s matches base
		for(typename DestContainerType::iterator r = res.begin(); r != res.end(); ) {
			if(r->isSubsetOf(ua)) goto nonMinimal;
			if(ua.isSubsetOf(*r)) {
				r = res.erase(r);
			}
			else {
				r++;
			}
		}
		res.insert(ua);
		nonMinimal:;
	}
}

template<typename SourceContainerType>
void composeCliques(const SourceContainerType& src, std::map< int, std::set< pencilmarks > >& cliques, int clSizeLimit) {
	cliques.clear();
	int size = 2;
	bool passIsEmpty = true;
	for(auto&& ua1 : src) {
		for(auto&& ua2 : src) {
			if(ua1.isDisjoint(ua2)) {
				pencilmarks u(ua1);
				u |= ua2;
				cliques[2].insert(u);
				passIsEmpty = false;
			}
		}
	}
	while(!passIsEmpty && size < clSizeLimit) {
		size++;
		passIsEmpty = true;
		for(auto&& ua1 : cliques[size - 1]) {
			for(auto&& ua2 : src) {
				if(ua1.isDisjoint(ua2)) {
					pencilmarks u(ua1);
					u |= ua2;
					cliques[size].insert(u);
					passIsEmpty = false;
				}
			}
		}
	}
}

puzClueRemover::puzClueRemover(const pencilmarks& puzzle, int numCluesToRemove_, int maxSolutionCount_) :
	original(puzzle),
	numCluesToRemove(numCluesToRemove_),
	maxSolutionCount(maxSolutionCount_) {
	pencilmarks pm(original);
	fsss2::countSolutions solCounter;
	int maxM1 = 1 + maxSolutionCount - numCluesToRemove;
	cluesToRemove[0] = -1; //mark as unknown
	for(int d = 0; d < 9; d++) {
		for(int c = 0; c < 81; c++) {
			numSolsForMinus1[81 * d + c] = -1;
			if(!pm[d].isBitSet(c)) continue;
			pm[d].clearBit(c);
			numSolsForMinus1[81 * d + c] = solCounter.solve(pm, 1 + maxM1);
			if(cluesToRemove[0] == -1 && numSolsForMinus1[81 * d + c] != -1) {
				cluesToRemove[0] = 81 * d + c; //initial position
			}
			if(numSolsForMinus1[81 * d + c] == 0) {
				printf("Puzzle w/o solution\n");
			}
			pm[d].setBit(c);
		}
	}
	for(int cl = 1; cl < numCluesToRemove; cl++) {
		cluesToRemove[cl] = -1;
		if(cluesToRemove[cl - 1] != -1) {
			for(int pos = 1 + cluesToRemove[cl - 1]; pos < 729; pos++) {
				if(numSolsForMinus1[pos] != -1) {
					cluesToRemove[cl] = pos;
					break;
				}
			}
		}
	}
}

bool puzClueRemover::next(pencilmarks& reducedPuzzle) {
	if(cluesToRemove[numCluesToRemove - 1] == -1) return false;
	reducedPuzzle = original;
	for(int cl = 0; cl < numCluesToRemove; cl++) {
		int c = cluesToRemove[cl];
		if(c < 0 || c >= 729) {
			printf("cluesToRemove[%d]=%d\n", cl, c);
			exit(1);
		}
		reducedPuzzle[c / 81].clearBit(c % 81);
	}
	//find next
	for(int clForPosChange = numCluesToRemove - 1; clForPosChange >= 0; clForPosChange--) { //go backward
		int newPos = -1;
		for(int pos = cluesToRemove[clForPosChange] + 1; pos < 729; pos++) {
			if(numSolsForMinus1[pos] != -1) {
				newPos = pos;
				break;
			}
		}
		if(newPos != -1) { // go forward
			cluesToRemove[clForPosChange] = newPos;
			for(int cl = clForPosChange + 1; cl < numCluesToRemove; cl++) {
				cluesToRemove[cl] = -1;
				for(int pos = 1 + cluesToRemove[cl - 1]; pos < 729; pos++) {
					if(numSolsForMinus1[pos] != -1) {
						cluesToRemove[cl] = pos;
						break;
					}
				}
			}
		}
		else {
			cluesToRemove[numCluesToRemove - 1] = -1; //exhausted
		}
	}
	return true;
}


lowSolutionsCount::lowSolutionsCount() {
	// TODO Auto-generated constructor stub

}

lowSolutionsCount::~lowSolutionsCount() {
	// TODO Auto-generated destructor stub
}

int lowSolutionsCount::cmdLowSolAnalyze() {
	int ret = 0;
	char line[2000];
	lowSolutionsCount ls;
	ls.knownMinExtraConstraints = opt.getIntValue("numclues", 1);
	if(ls.knownMinExtraConstraints <= 0) return 1;
	if(ls.knownMinExtraConstraints > puzClueRemover::cluesLimit) return 1; //I live in a real world
	ls.numSolutions = opt.getIntValue("numsolutions", 100);
	if(ls.numSolutions <= 0) return 1;
	//Assuming the input has no redundant clues. Then remoival of first clue gives at least 2 solutions, and removal of each next adds at least one solutions.
	//if(ls.knownMinExtraConstraints > 1 + ls.numSolutions) return 1; //too low number of solutions or too high number of clues to remove
	int nPuzzles = 0;
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm;
		if(!pm.fromChars729(line)) {
			ret = 1;
			continue;
		}
		ls.addMatching(pm);
		nPuzzles++;
		//getStatistics(pm);
	}
//	fsss2::isRedundant redundancyChecker;
	printf("Puzzles processed = %d\n", nPuzzles);
	printf("Signatures found = %d\n", (int)ls.partitions.size());
	for(auto&& s : ls.partitions) {
		pencilmarks pmCommon(s.first);
		std::cout << "\nSignature (" << pmCommon.popcount() << "):\n" << pmCommon << std::endl;
		std::cout << "Solutions (" << s.second.solutions.size() << "):\n";
		std::set< std::string > solsDistinct;
		for(auto&& p : s.second.solutions) {
			char gr[81];
			char grCan[81];
			fsss2::getAnySolution solver;
			solver.solve(p, gr);
			solRowMinLex::rowMinLex(gr, grCan);
			for(int i = 0; i < 81; i++) gr[i] += '0';
			std::string sOrig(gr, gr + 81);
			std::cout << sOrig << std::endl;
			for(int i = 0; i < 81; i++) grCan[i] += '0';
			std::string sCan(grCan, grCan + 81);
			solsDistinct.insert(sCan);
			pmCommon &= p; //leave only common to all solutions clues
		}
		std::cout << "ED solutions: " << solsDistinct.size() << std::endl;
		std::cout << "Common clues (" << pmCommon.popcount() << "):\n" << pmCommon << std::endl;
		pencilmarks pmDifferent(s.first);
		pmDifferent.clearBits(pmCommon);
		std::cout << "Different clues (" << pmDifferent.popcount() << "):\n" << pmDifferent << std::endl;
		//for(auto&& g : solsDistinct) {
		//	printf("\t%s\n", g.c_str());
		//}
		printf("Pencilmarks occupied %d\n", (int)pmDifferent.popcount());
		bm128 cellsDifferent;
		cellsDifferent.clear();
		for(int d = 0; d < 9; d++) {
			cellsDifferent |= pmDifferent[d];
		}
		printf("Cells occupied %d\n", (int)cellsDifferent.popcount_128());

//		for(auto&& p : s.second.solutions) {
//			pencilmarks lowCluesPart(p);
//			lowCluesPart.clearBits(pmCommon);
//			printf("\n");
//			for(auto&& pp : s.second.externalConstraints) {
//				pencilmarks pTest(pp);
//				pTest |= lowCluesPart;
//				for(int d = 0; d < 9; d++) {
//					for(int c = 0; c < 81; c++) {
//						if(!pTest[d].isBitSet(c)) continue; //no constraint there
//						if(pmDifferent[d].isBitSet(c)) continue; //don't test constraints set by low-clues part
//						bool isRedundant = redundancyChecker.solve(pTest, d, c);
//						printf("%c", isRedundant ? 'R' : 'n');
//					}
//				}
//				printf("\n");
//			}
//		}

		std::set< pencilmarks > xua;
		std::map< int, std::set< pencilmarks > > cliques;
		int solNum = 0;
		for(auto&& p : s.second.solutions) {
			getXua(p, s.second.solutions, xua);
			//printf("UA: %d\n", int(xua.size()));
			composeCliques(xua, cliques, ls.knownMinExtraConstraints + 1);
			if(!cliques.empty()) {
				//int maxClSize = cliques.rbegin()->first;
				//int numMaxCliques = cliques.rbegin()->second.size();
				//printf("MaxCliqueSize = %d (%d)\n", maxClSize, numMaxCliques);
				std::cout << "Solution " << solNum << "\tNumUA " << xua.size() << "\tMaxCliqueSize " << cliques.rbegin()->first << "\tnumMaxCliques " << cliques.rbegin()->second.size() << std::endl;
			}
			++solNum;
		}
		std::cout << "Known externalConstraints (" << s.second.externalConstraints.size() << "):" << std::endl;
		for(auto&& ec : s.second.externalConstraints) {
			pencilmarks e(ec);
			e.clearBits(pmCommon);
			std::cout << e << std::endl;
		}
	}
	return ret;
}

void lowSolutionsCount::addMatching(const pencilmarks& puz) {
	fsss2::getNSolutions solEnumerator;
	puzClueRemover minusN(puz, knownMinExtraConstraints, numSolutions);
	pencilmarks reducedPm;
	pencilmarks* allSol = new pencilmarks[numSolutions + 1];
	while(minusN.next(reducedPm)) {
		int nSol = solEnumerator.solve(reducedPm, allSol, numSolutions + 1);
		//if(nSol != numSolutions) continue;
		if(nSol == -1) continue;
		//compose signature = union of solutions
		pencilmarks signature;
		signature.clear();
		for(int i = 0; i < nSol; i++) {
			signature |= allSol[i];
		}
		auto found = partitions.find(signature);
		if(found != partitions.end()) { //all solutions were previously inserted, just add the puzzle
			found->second.externalConstraints.insert(puz);
			//printf(".");
		}
		else {
			auto&& newPart = partitions[signature];
			newPart.externalConstraints.insert(puz);
			newPart.solutions.insert(allSol, allSol + nSol);
			//printf("+");
		}
	}
	delete[] allSol;
}

void lowSolutionsCount::getStatistics(const pencilmarks& puz) {
	puzzleInvariants pInv(puz);
	std::map< int, int, std::greater<int> > numConstraintsPerDigitDistr;
	std::map< int, int, std::greater<int> > numConstraintsPerCellDistr;
	std::map< int, int, std::greater<int> > numConstraintsPerBoxDistr;

	pInv.getBasicInvariants();
	for(int b = 0; b < 9; b++) {
		numConstraintsPerBoxDistr[pInv.numConstraintsInBox[b]]++;
		numConstraintsPerDigitDistr[pInv.numConstraintsForDigit[b]]++;
	}
	for(int c = 0; c < 81; c++) {
		numConstraintsPerCellDistr[pInv.numConstraintsInCell[c]]++;
	}
	printf("\nConstraints per digit");
	for(auto&& p : numConstraintsPerDigitDistr) {
		printf("\t%d*%d", p.first, p.second);
	}
	printf("\nConstraints per cell");
	for(auto&& p : numConstraintsPerCellDistr) {
		printf("\t%d*%d", p.first, p.second);
	}
	printf("\nConstraints per box");
	for(auto&& p : numConstraintsPerBoxDistr) {
		printf("\t%d*%d", p.first, p.second);
	}
	printf("\n");
}
