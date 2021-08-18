/*
 * lowSolutionsCount.h
 *
 *  Created on: Dec 12, 2020
 *      Author: mladen
 */

#ifndef LOWSOLUTIONSCOUNT_H_
#define LOWSOLUTIONSCOUNT_H_

#include "fsss2.h"
#include <map>
#include <set>

class lowSolutionsCount {
public:
	struct parts {
		std::set< pencilmarks > solutions;
		std::set< pencilmarks > externalConstraints;
	};
	int numSolutions;
	int knownMinExtraConstraints;
	std::map< pencilmarks, parts > partitions;
	lowSolutionsCount();
	virtual ~lowSolutionsCount();
	static int cmdLowSolAnalyze();
	static void getStatistics(const pencilmarks& puz);
	void addMatching(const pencilmarks& puz);
    friend std::ostream & operator <<(std::ostream& out, const lowSolutionsCount& e) {
    	//out << std::string(e);
    	return out;
    }
    friend std::istream & operator >>(std::istream& in, lowSolutionsCount& e) {
//    	std::string s;
//    	in >> s;
//    	edgesInEgraphBM tmp(s);
//    	e = tmp;
    	return in;
    }
};

struct puzClueRemover {
	static constexpr int cluesLimit = 30;
	pencilmarks original;
	int numCluesToRemove;
	int maxSolutionCount;
	int numSolsForMinus1[729];
	int cluesToRemove[cluesLimit];
	puzClueRemover(const pencilmarks& puzzle, int numCluesToRemove_, int maxSolutionCount_);
	//~puzClueRemover();
	bool next(pencilmarks& reducedPuzzle);
};
#endif /* LOWSOLUTIONSCOUNT_H_ */
