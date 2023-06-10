/*
 * cmdBackdoor.cpp
 *
 *  Created on: Sep 29, 2019
 *      Author: Mladen Dobrichev
 */

#include <iostream>
#include "cmdSolve.h"
#include "options.h"
#include "fsss2.h"

cmdBackdoor::cmdBackdoor() {
	vanilla = opt.getFlag("vanilla");
}
int cmdBackdoor::exec() {
	char line[2000];
	while(std::cin.getline(line, sizeof(line))) {
		pencilmarks pm{};
		if(vanilla) {
			pm.fromChars81(line);
		}
		else {
			if(!pm.fromChars729(line)) return 1;
		}
		findBackdoor(pm);
	}
	return 0;
}
void cmdBackdoor::findBackdoor(const pencilmarks& pmInitial) { //puzzle in 729-columns format, backdoorSize
	pencilmarks pmExemplar;
	pencilmarks pm(pmInitial);
	fsss2::getSingleSolution ss;
	fsss2::noGuess ng;
	char sol[88];
	char outPuz[729];
	char outPuz2[729];
	bm128 givens;
	//int nonGivenCells[81];
	//int numNonGivenCells = 0;
	givens.clear();
	ng.reduce(pm);
	for(int c = 0; c < 81; c++) {
		int numAllowed = 0;
		for(int d = 0; d < 9; d++) {
			if(!pm[d].isBitSet(c)) {
				if(numAllowed) {
					//nonGivenCells[numNonGivenCells++] = c;
					goto nextCell;
				}
				numAllowed++;
			}
		}
		givens.setBit(c);
		nextCell:;
	}
	//printf("NumGivens=%d\n", givens.popcount_96());fflush(NULL);
	if(1 != ss.solve(pm, sol)) return;
	//printf("0");fflush(NULL);
	int minBD = 0;
	pmExemplar = pm;
	if(!ng.solve(pm)) {
		printf("1");
		minBD = 1;
		for(int c1 = 0; c1 < 81; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			if(ng.solve(pm1)) {
				pmExemplar = pm1;
				goto done;
			}
		}
		//printf("2");fflush(NULL);
		minBD = 2;
		for(int c1 = 0; c1 < 81 - 1; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 0; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				if(ng.solve(pm2)) {
					pmExemplar = pm2;
					goto done;
				}
			}
		}
		//printf("3");fflush(NULL);
		minBD = 3;
		for(int c1 = 0; c1 < 81 - 2; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 1; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				for(int c3 = c2 + 1; c3 < 81 - 0; c3++) {
					if(givens.isBitSet(c3)) continue;
					pencilmarks pm3(pm2);
					pm3.forceCell(c3, sol[c3] - 1);
					if(ng.solve(pm3)) {
						pmExemplar = pm3;
						goto done;
					}
				}
			}
		}
		//printf("4");fflush(NULL);
		minBD = 4;
		for(int c1 = 0; c1 < 81 - 3; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 2; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				for(int c3 = c2 + 1; c3 < 81 - 1; c3++) {
					if(givens.isBitSet(c3)) continue;
					pencilmarks pm3(pm2);
					pm3.forceCell(c3, sol[c3] - 1);
					for(int c4 = c3 + 1; c4 < 81 - 0; c4++) {
						if(givens.isBitSet(c4)) continue;
						pencilmarks pm4(pm3);
						pm4.forceCell(c4, sol[c4] - 1);
						if(ng.solve(pm4)) {
							pmExemplar = pm4;
							goto done;
						}
					}
				}
			}
		}
		//printf("5");fflush(NULL);
		minBD = 5;
		for(int c1 = 0; c1 < 81 - 4; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 3; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				for(int c3 = c2 + 1; c3 < 81 - 2; c3++) {
					if(givens.isBitSet(c3)) continue;
					pencilmarks pm3(pm2);
					pm3.forceCell(c3, sol[c3] - 1);
					for(int c4 = c3 + 1; c4 < 81 - 1; c4++) {
						if(givens.isBitSet(c4)) continue;
						pencilmarks pm4(pm3);
						pm4.forceCell(c4, sol[c4] - 1);
						for(int c5 = c4 + 1; c5 < 81 - 0; c5++) {
							if(givens.isBitSet(c5)) continue;
							pencilmarks pm5(pm4);
							pm5.forceCell(c5, sol[c5] - 1);
							if(ng.solve(pm5)) {
								pmExemplar = pm5;
								goto done;
							}
						}
					}
				}
			}
		}
		//printf("6");fflush(NULL);
		minBD = 6;
		for(int c1 = 0; c1 < 81 - 5; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 4; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				for(int c3 = c2 + 1; c3 < 81 - 3; c3++) {
					if(givens.isBitSet(c3)) continue;
					pencilmarks pm3(pm2);
					pm3.forceCell(c3, sol[c3] - 1);
					for(int c4 = c3 + 1; c4 < 81 - 2; c4++) {
						if(givens.isBitSet(c4)) continue;
						pencilmarks pm4(pm3);
						pm4.forceCell(c4, sol[c4] - 1);
						for(int c5 = c4 + 1; c5 < 81 - 1; c5++) {
							if(givens.isBitSet(c5)) continue;
							pencilmarks pm5(pm4);
							pm5.forceCell(c5, sol[c5] - 1);
							for(int c6 = c5 + 1; c6 < 81 - 0; c6++) {
								if(givens.isBitSet(c6)) continue;
								pencilmarks pm6(pm5);
								pm6.forceCell(c6, sol[c6] - 1);
								if(ng.solve(pm6)) {
									pmExemplar = pm6;
									goto done;
								}
							}
						}
					}
				}
			}
		}
		//printf("7");fflush(NULL);
		minBD = 7;
		for(int c1 = 0; c1 < 81 - 6; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 5; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				for(int c3 = c2 + 1; c3 < 81 - 4; c3++) {
					if(givens.isBitSet(c3)) continue;
					pencilmarks pm3(pm2);
					pm3.forceCell(c3, sol[c3] - 1);
					for(int c4 = c3 + 1; c4 < 81 - 3; c4++) {
						if(givens.isBitSet(c4)) continue;
						pencilmarks pm4(pm3);
						pm4.forceCell(c4, sol[c4] - 1);
						for(int c5 = c4 + 1; c5 < 81 - 2; c5++) {
							if(givens.isBitSet(c5)) continue;
							pencilmarks pm5(pm4);
							pm5.forceCell(c5, sol[c5] - 1);
							for(int c6 = c5 + 1; c6 < 81 - 1; c6++) {
								if(givens.isBitSet(c6)) continue;
								pencilmarks pm6(pm5);
								pm6.forceCell(c6, sol[c6] - 1);
								for(int c7 = c6 + 1; c7 < 81 - 0; c7++) {
									if(givens.isBitSet(c7)) continue;
									pencilmarks pm7(pm6);
									pm7.forceCell(c7, sol[c7] - 1);
									if(ng.solve(pm7)) {
										pmExemplar = pm7;
										goto done;
									}
								}
							}
						}
					}
				}
			}
		}
		//printf("8");fflush(NULL);
		minBD = 8;
		for(int c1 = 0; c1 < 81 - 7; c1++) {
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 6; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				for(int c3 = c2 + 1; c3 < 81 - 5; c3++) {
					if(givens.isBitSet(c3)) continue;
					pencilmarks pm3(pm2);
					pm3.forceCell(c3, sol[c3] - 1);
					for(int c4 = c3 + 1; c4 < 81 - 4; c4++) {
						if(givens.isBitSet(c4)) continue;
						pencilmarks pm4(pm3);
						pm4.forceCell(c4, sol[c4] - 1);
						for(int c5 = c4 + 1; c5 < 81 - 3; c5++) {
							if(givens.isBitSet(c5)) continue;
							pencilmarks pm5(pm4);
							pm5.forceCell(c5, sol[c5] - 1);
							for(int c6 = c5 + 1; c6 < 81 - 2; c6++) {
								if(givens.isBitSet(c6)) continue;
								pencilmarks pm6(pm5);
								pm6.forceCell(c6, sol[c6] - 1);
								for(int c7 = c6 + 1; c7 < 81 - 1; c7++) {
									if(givens.isBitSet(c7)) continue;
									pencilmarks pm7(pm6);
									pm7.forceCell(c7, sol[c7] - 1);
									for(int c8 = c7 + 1; c8 < 81 - 0; c8++) {
										if(givens.isBitSet(c8)) continue;
										pencilmarks pm8(pm7);
										pm8.forceCell(c8, sol[c8] - 1);
										if(ng.solve(pm8)) {
											pmExemplar = pm8;
											goto done;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		//printf("9");fflush(NULL);
		minBD = 9;
		for(int c1 = 0; c1 < 81 - 8; c1++) { // this takes days
			if(givens.isBitSet(c1)) continue;
			pencilmarks pm1(pm);
			pm1.forceCell(c1, sol[c1] - 1);
			for(int c2 = c1 + 1; c2 < 81 - 7; c2++) {
				if(givens.isBitSet(c2)) continue;
				pencilmarks pm2(pm1);
				pm2.forceCell(c2, sol[c2] - 1);
				for(int c3 = c2 + 1; c3 < 81 - 6; c3++) {
					if(givens.isBitSet(c3)) continue;
					pencilmarks pm3(pm2);
					pm3.forceCell(c3, sol[c3] - 1);
					for(int c4 = c3 + 1; c4 < 81 - 5; c4++) {
						if(givens.isBitSet(c4)) continue;
						pencilmarks pm4(pm3);
						pm4.forceCell(c4, sol[c4] - 1);
						for(int c5 = c4 + 1; c5 < 81 - 4; c5++) {
							if(givens.isBitSet(c5)) continue;
							pencilmarks pm5(pm4);
							pm5.forceCell(c5, sol[c5] - 3);
							for(int c6 = c5 + 1; c6 < 81 - 0; c6++) {
								if(givens.isBitSet(c6)) continue;
								pencilmarks pm6(pm5);
								pm6.forceCell(c6, sol[c6] - 1);
								for(int c7 = c6 + 1; c7 < 81 - 2; c7++) {
									if(givens.isBitSet(c7)) continue;
									pencilmarks pm7(pm6);
									pm7.forceCell(c7, sol[c7] - 1);
									for(int c8 = c7 + 1; c8 < 81 - 1; c8++) {
										if(givens.isBitSet(c8)) continue;
										pencilmarks pm8(pm7);
										pm8.forceCell(c8, sol[c8] - 1);
										for(int c9 = c8 + 1; c9 < 81 - 0; c9++) {
											if(givens.isBitSet(c9)) continue;
											pencilmarks pm9(pm8);
											pm8.forceCell(c9, sol[c9] - 1);
											if(ng.solve(pm9)) {
												pmExemplar = pm9;
												goto done;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		minBD = 99;
	}
	done:
	pm.toChars729(outPuz);
	pmExemplar.toChars729(outPuz2);
	//printf("\n");fflush(NULL);
	printf("%729.729s\t%d\t%729.729s\n", outPuz, minBD, outPuz2);
	fflush(NULL);
}

//void cmdBackdoor::findBackdoor(const pencilmarks& pm) { //puzzle in 729-columns format, backdoorSize
//	pencilmarks pmExemplar;
//	fsss2::getSingleSolution ss;
//	fsss2::noGuess ng;
//	char sol[88];
//	char outPuz[729];
//	char outPuz2[729];
//	bm128 givens;
//	givens.clear();
//	for(int c = 0; c < 81; c++) {
//		int numAllowed = 0;
//		for(int d = 0; d < 9; d++) {
//			if(!pm[d].isBitSet(c)) {
//				if(numAllowed) goto nextCell;
//				numAllowed++;
//			}
//		}
//		givens.setBit(c);
//		nextCell:;
//	}
//	if(1 != ss.solve(pm, sol)) return;
//	int minBD = 0;
//	pmExemplar = pm;
//	if(!ng.solve(pm)) {
//		minBD = 1;
//		for(int c1 = 0; c1 < 81; c1++) {
//			if(givens.isBitSet(c1)) continue;
//			pencilmarks pm1(pm);
//			pm1.forceCell(c1, sol[c1] - 1);
//			if(ng.solve(pm1)) {
//				pmExemplar = pm1;
//				goto done;
//			}
//		}
//		minBD = 2;
//		for(int c1 = 0; c1 < 81 - 1; c1++) {
//			if(givens.isBitSet(c1)) continue;
//			pencilmarks pm1(pm);
//			pm1.forceCell(c1, sol[c1] - 1);
//			for(int c2 = c1 + 1; c2 < 81 - 0; c2++) {
//				if(givens.isBitSet(c2)) continue;
//				pencilmarks pm2(pm1);
//				pm2.forceCell(c2, sol[c2] - 1);
//				if(ng.solve(pm2)) {
//					pmExemplar = pm2;
//					goto done;
//				}
//			}
//		}
//		minBD = 3;
//		for(int c1 = 0; c1 < 81 - 2; c1++) {
//			if(givens.isBitSet(c1)) continue;
//			pencilmarks pm1(pm);
//			pm1.forceCell(c1, sol[c1] - 1);
//			for(int c2 = c1 + 1; c2 < 81 - 1; c2++) {
//				if(givens.isBitSet(c2)) continue;
//				pencilmarks pm2(pm1);
//				pm2.forceCell(c2, sol[c2] - 1);
//				for(int c3 = c2 + 1; c3 < 81 - 0; c3++) {
//					if(givens.isBitSet(c3)) continue;
//					pencilmarks pm3(pm2);
//					pm3.forceCell(c3, sol[c3] - 1);
//					if(ng.solve(pm3)) {
//						pmExemplar = pm3;
//						goto done;
//					}
//				}
//			}
//		}
//		minBD = 4;
//		for(int c1 = 0; c1 < 81 - 3; c1++) {
//			if(givens.isBitSet(c1)) continue;
//			pencilmarks pm1(pm);
//			pm1.forceCell(c1, sol[c1] - 1);
//			for(int c2 = c1 + 1; c2 < 81 - 2; c2++) {
//				if(givens.isBitSet(c2)) continue;
//				pencilmarks pm2(pm1);
//				pm2.forceCell(c2, sol[c2] - 1);
//				for(int c3 = c2 + 1; c3 < 81 - 1; c3++) {
//					if(givens.isBitSet(c3)) continue;
//					pencilmarks pm3(pm2);
//					pm3.forceCell(c3, sol[c3] - 1);
//					for(int c4 = c3 + 1; c4 < 81 - 0; c4++) {
//						if(givens.isBitSet(c4)) continue;
//						pencilmarks pm4(pm3);
//						pm4.forceCell(c4, sol[c4] - 1);
//						if(ng.solve(pm4)) {
//							pmExemplar = pm4;
//							goto done;
//						}
//					}
//				}
//			}
//		}
//		minBD = 5;
//		for(int c1 = 0; c1 < 81 - 4; c1++) {
//			if(givens.isBitSet(c1)) continue;
//			pencilmarks pm1(pm);
//			pm1.forceCell(c1, sol[c1] - 1);
//			for(int c2 = c1 + 1; c2 < 81 - 3; c2++) {
//				if(givens.isBitSet(c2)) continue;
//				pencilmarks pm2(pm1);
//				pm2.forceCell(c2, sol[c2] - 1);
//				for(int c3 = c2 + 1; c3 < 81 - 2; c3++) {
//					if(givens.isBitSet(c3)) continue;
//					pencilmarks pm3(pm2);
//					pm3.forceCell(c3, sol[c3] - 1);
//					for(int c4 = c3 + 1; c4 < 81 - 1; c4++) {
//						if(givens.isBitSet(c4)) continue;
//						pencilmarks pm4(pm3);
//						pm4.forceCell(c4, sol[c4] - 1);
//						for(int c5 = c4 + 1; c5 < 81 - 0; c5++) {
//							if(givens.isBitSet(c5)) continue;
//							pencilmarks pm5(pm4);
//							pm5.forceCell(c5, sol[c5] - 1);
//							if(ng.solve(pm5)) {
//								pmExemplar = pm5;
//								goto done;
//							}
//						}
//					}
//				}
//			}
//		}
//		minBD = 6;
//		for(int c1 = 0; c1 < 81 - 5; c1++) {
//			if(givens.isBitSet(c1)) continue;
//			pencilmarks pm1(pm);
//			pm1.forceCell(c1, sol[c1] - 1);
//			for(int c2 = c1 + 1; c2 < 81 - 4; c2++) {
//				if(givens.isBitSet(c2)) continue;
//				pencilmarks pm2(pm1);
//				pm2.forceCell(c2, sol[c2] - 1);
//				for(int c3 = c2 + 1; c3 < 81 - 3; c3++) {
//					if(givens.isBitSet(c3)) continue;
//					pencilmarks pm3(pm2);
//					pm3.forceCell(c3, sol[c3] - 1);
//					for(int c4 = c3 + 1; c4 < 81 - 2; c4++) {
//						if(givens.isBitSet(c4)) continue;
//						pencilmarks pm4(pm3);
//						pm4.forceCell(c4, sol[c4] - 1);
//						for(int c5 = c4 + 1; c5 < 81 - 1; c5++) {
//							if(givens.isBitSet(c5)) continue;
//							pencilmarks pm5(pm4);
//							pm5.forceCell(c5, sol[c5] - 1);
//							for(int c6 = c5 + 1; c6 < 81 - 0; c6++) {
//								if(givens.isBitSet(c6)) continue;
//								pencilmarks pm6(pm5);
//								pm6.forceCell(c6, sol[c6] - 1);
//								if(ng.solve(pm6)) {
//									pmExemplar = pm6;
//									goto done;
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//		minBD = 99;
//	}
//	done:
//	pm.toChars729(outPuz);
//	pmExemplar.toChars729(outPuz2);
//	printf("%729.729s\t%d\t%729.729s\n", outPuz, minBD, outPuz2);
//	fflush(NULL);
//}
