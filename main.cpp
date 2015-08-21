/*
 * main.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Mladen Dobrichev
 */

//for testing fsss2 sudoku solver

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "fsss2.h"

//void	printVisibleCells();
//void printTripletMasks();
//void	printBitsForHouse();
//void printHouseBits();
//#include "tables.h"

//int nNaked[129]; //debug
//int a = 0;
//int b = 0;

////#define COUNT_TRIALS

#ifdef COUNT_TRIALS
int nTrials = 0;
#endif

int main(int argc, char* argv[])
{
	//printVisibleCells();
	//printBitsForHouse();
	//printHouseBits();
	//return 0;

	clock_t start, finish;
	int ret = 0;
	start = clock();

	char p[2000];
	char c[88];
	//isIrreducible ss;
	hasSingleSolution ss;
	//hasAnySolution ss;
	int num[3] = {0,0,0};
	while(fgets(p, sizeof(p), stdin)) {
		for(int i = 0; i < 81; i++) c[i] = (p[i] <= '9' && p[i] >='0' ? p[i] - '0' : 0);
		num[ss.solve(c)]++; //test hasAnySolution, hasSingleSolution
		//num[ss.solve(c) ? 0 : 1]++; // test isIrreducible
	}


	finish = clock();
#ifdef COUNT_TRIALS
	fprintf(stderr, "%d+%d+%d puzzles in %2.3f seconds. Trials = %d.\n", num[0], num[1], num[2], (double)(finish - start) / CLOCKS_PER_SEC, nTrials);
#else
	fprintf(stderr, "%d+%d+%d puzzles in %2.3f seconds.\n", num[0], num[1], num[2], (double)(finish - start) / CLOCKS_PER_SEC);
#endif
//	for(int n = 0; n < 20; n++)
//		fprintf(stderr, "naked[%d] = %d\n", n, nNaked[n]);
	//fprintf(stderr, "a = %d, b = %d\n", a, b);
	return ret;
}

/////////////////////////////////////////////

////temporary and debug functions
//void bm128toHex(const bm128& v) {
//	printf("{0x%016.16lX,0x%016.16lX},\n", v.bitmap128.m128i_u64[0], v.bitmap128.m128i_u64[1]);
//}
//
//extern const int affectedCells[81][20] =
//{
//	{ 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,18,19,20,27,36,45,54,63,72},
//	{ 0, 2, 3, 4, 5, 6, 7, 8, 9,10,11,18,19,20,28,37,46,55,64,73},
//	{ 0, 1, 3, 4, 5, 6, 7, 8, 9,10,11,18,19,20,29,38,47,56,65,74},
//	{ 0, 1, 2, 4, 5, 6, 7, 8,12,13,14,21,22,23,30,39,48,57,66,75},
//	{ 0, 1, 2, 3, 5, 6, 7, 8,12,13,14,21,22,23,31,40,49,58,67,76},
//	{ 0, 1, 2, 3, 4, 6, 7, 8,12,13,14,21,22,23,32,41,50,59,68,77},
//	{ 0, 1, 2, 3, 4, 5, 7, 8,15,16,17,24,25,26,33,42,51,60,69,78},
//	{ 0, 1, 2, 3, 4, 5, 6, 8,15,16,17,24,25,26,34,43,52,61,70,79},
//	{ 0, 1, 2, 3, 4, 5, 6, 7,15,16,17,24,25,26,35,44,53,62,71,80},
//	{ 0, 1, 2,10,11,12,13,14,15,16,17,18,19,20,27,36,45,54,63,72},
//	{ 0, 1, 2, 9,11,12,13,14,15,16,17,18,19,20,28,37,46,55,64,73},
//	{ 0, 1, 2, 9,10,12,13,14,15,16,17,18,19,20,29,38,47,56,65,74},
//	{ 3, 4, 5, 9,10,11,13,14,15,16,17,21,22,23,30,39,48,57,66,75},
//	{ 3, 4, 5, 9,10,11,12,14,15,16,17,21,22,23,31,40,49,58,67,76},
//	{ 3, 4, 5, 9,10,11,12,13,15,16,17,21,22,23,32,41,50,59,68,77},
//	{ 6, 7, 8, 9,10,11,12,13,14,16,17,24,25,26,33,42,51,60,69,78},
//	{ 6, 7, 8, 9,10,11,12,13,14,15,17,24,25,26,34,43,52,61,70,79},
//	{ 6, 7, 8, 9,10,11,12,13,14,15,16,24,25,26,35,44,53,62,71,80},
//	{ 0, 1, 2, 9,10,11,19,20,21,22,23,24,25,26,27,36,45,54,63,72},
//	{ 0, 1, 2, 9,10,11,18,20,21,22,23,24,25,26,28,37,46,55,64,73},
//	{ 0, 1, 2, 9,10,11,18,19,21,22,23,24,25,26,29,38,47,56,65,74},
//	{ 3, 4, 5,12,13,14,18,19,20,22,23,24,25,26,30,39,48,57,66,75},
//	{ 3, 4, 5,12,13,14,18,19,20,21,23,24,25,26,31,40,49,58,67,76},
//	{ 3, 4, 5,12,13,14,18,19,20,21,22,24,25,26,32,41,50,59,68,77},
//	{ 6, 7, 8,15,16,17,18,19,20,21,22,23,25,26,33,42,51,60,69,78},
//	{ 6, 7, 8,15,16,17,18,19,20,21,22,23,24,26,34,43,52,61,70,79},
//	{ 6, 7, 8,15,16,17,18,19,20,21,22,23,24,25,35,44,53,62,71,80},
//	{ 0, 9,18,28,29,30,31,32,33,34,35,36,37,38,45,46,47,54,63,72},
//	{ 1,10,19,27,29,30,31,32,33,34,35,36,37,38,45,46,47,55,64,73},
//	{ 2,11,20,27,28,30,31,32,33,34,35,36,37,38,45,46,47,56,65,74},
//	{ 3,12,21,27,28,29,31,32,33,34,35,39,40,41,48,49,50,57,66,75},
//	{ 4,13,22,27,28,29,30,32,33,34,35,39,40,41,48,49,50,58,67,76},
//	{ 5,14,23,27,28,29,30,31,33,34,35,39,40,41,48,49,50,59,68,77},
//	{ 6,15,24,27,28,29,30,31,32,34,35,42,43,44,51,52,53,60,69,78},
//	{ 7,16,25,27,28,29,30,31,32,33,35,42,43,44,51,52,53,61,70,79},
//	{ 8,17,26,27,28,29,30,31,32,33,34,42,43,44,51,52,53,62,71,80},
//	{ 0, 9,18,27,28,29,37,38,39,40,41,42,43,44,45,46,47,54,63,72},
//	{ 1,10,19,27,28,29,36,38,39,40,41,42,43,44,45,46,47,55,64,73},
//	{ 2,11,20,27,28,29,36,37,39,40,41,42,43,44,45,46,47,56,65,74},
//	{ 3,12,21,30,31,32,36,37,38,40,41,42,43,44,48,49,50,57,66,75},
//	{ 4,13,22,30,31,32,36,37,38,39,41,42,43,44,48,49,50,58,67,76},
//	{ 5,14,23,30,31,32,36,37,38,39,40,42,43,44,48,49,50,59,68,77},
//	{ 6,15,24,33,34,35,36,37,38,39,40,41,43,44,51,52,53,60,69,78},
//	{ 7,16,25,33,34,35,36,37,38,39,40,41,42,44,51,52,53,61,70,79},
//	{ 8,17,26,33,34,35,36,37,38,39,40,41,42,43,51,52,53,62,71,80},
//	{ 0, 9,18,27,28,29,36,37,38,46,47,48,49,50,51,52,53,54,63,72},
//	{ 1,10,19,27,28,29,36,37,38,45,47,48,49,50,51,52,53,55,64,73},
//	{ 2,11,20,27,28,29,36,37,38,45,46,48,49,50,51,52,53,56,65,74},
//	{ 3,12,21,30,31,32,39,40,41,45,46,47,49,50,51,52,53,57,66,75},
//	{ 4,13,22,30,31,32,39,40,41,45,46,47,48,50,51,52,53,58,67,76},
//	{ 5,14,23,30,31,32,39,40,41,45,46,47,48,49,51,52,53,59,68,77},
//	{ 6,15,24,33,34,35,42,43,44,45,46,47,48,49,50,52,53,60,69,78},
//	{ 7,16,25,33,34,35,42,43,44,45,46,47,48,49,50,51,53,61,70,79},
//	{ 8,17,26,33,34,35,42,43,44,45,46,47,48,49,50,51,52,62,71,80},
//	{ 0, 9,18,27,36,45,55,56,57,58,59,60,61,62,63,64,65,72,73,74},
//	{ 1,10,19,28,37,46,54,56,57,58,59,60,61,62,63,64,65,72,73,74},
//	{ 2,11,20,29,38,47,54,55,57,58,59,60,61,62,63,64,65,72,73,74},
//	{ 3,12,21,30,39,48,54,55,56,58,59,60,61,62,66,67,68,75,76,77},
//	{ 4,13,22,31,40,49,54,55,56,57,59,60,61,62,66,67,68,75,76,77},
//	{ 5,14,23,32,41,50,54,55,56,57,58,60,61,62,66,67,68,75,76,77},
//	{ 6,15,24,33,42,51,54,55,56,57,58,59,61,62,69,70,71,78,79,80},
//	{ 7,16,25,34,43,52,54,55,56,57,58,59,60,62,69,70,71,78,79,80},
//	{ 8,17,26,35,44,53,54,55,56,57,58,59,60,61,69,70,71,78,79,80},
//	{ 0, 9,18,27,36,45,54,55,56,64,65,66,67,68,69,70,71,72,73,74},
//	{ 1,10,19,28,37,46,54,55,56,63,65,66,67,68,69,70,71,72,73,74},
//	{ 2,11,20,29,38,47,54,55,56,63,64,66,67,68,69,70,71,72,73,74},
//	{ 3,12,21,30,39,48,57,58,59,63,64,65,67,68,69,70,71,75,76,77},
//	{ 4,13,22,31,40,49,57,58,59,63,64,65,66,68,69,70,71,75,76,77},
//	{ 5,14,23,32,41,50,57,58,59,63,64,65,66,67,69,70,71,75,76,77},
//	{ 6,15,24,33,42,51,60,61,62,63,64,65,66,67,68,70,71,78,79,80},
//	{ 7,16,25,34,43,52,60,61,62,63,64,65,66,67,68,69,71,78,79,80},
//	{ 8,17,26,35,44,53,60,61,62,63,64,65,66,67,68,69,70,78,79,80},
//	{ 0, 9,18,27,36,45,54,55,56,63,64,65,73,74,75,76,77,78,79,80},
//	{ 1,10,19,28,37,46,54,55,56,63,64,65,72,74,75,76,77,78,79,80},
//	{ 2,11,20,29,38,47,54,55,56,63,64,65,72,73,75,76,77,78,79,80},
//	{ 3,12,21,30,39,48,57,58,59,66,67,68,72,73,74,76,77,78,79,80},
//	{ 4,13,22,31,40,49,57,58,59,66,67,68,72,73,74,75,77,78,79,80},
//	{ 5,14,23,32,41,50,57,58,59,66,67,68,72,73,74,75,76,78,79,80},
//	{ 6,15,24,33,42,51,60,61,62,69,70,71,72,73,74,75,76,77,79,80},
//	{ 7,16,25,34,43,52,60,61,62,69,70,71,72,73,74,75,76,77,78,80},
//	{ 8,17,26,35,44,53,60,61,62,69,70,71,72,73,74,75,76,77,78,79}
//};
//extern const int affectedGroups[81][3] =
//{
//	{0, 9,18},{0,10,18},{0,11,18},{0,12,19},{0,13,19},{0,14,19},{0,15,20},{0,16,20},{0,17,20},
//	{1, 9,18},{1,10,18},{1,11,18},{1,12,19},{1,13,19},{1,14,19},{1,15,20},{1,16,20},{1,17,20},
//	{2, 9,18},{2,10,18},{2,11,18},{2,12,19},{2,13,19},{2,14,19},{2,15,20},{2,16,20},{2,17,20},
//	{3, 9,21},{3,10,21},{3,11,21},{3,12,22},{3,13,22},{3,14,22},{3,15,23},{3,16,23},{3,17,23},
//	{4, 9,21},{4,10,21},{4,11,21},{4,12,22},{4,13,22},{4,14,22},{4,15,23},{4,16,23},{4,17,23},
//	{5, 9,21},{5,10,21},{5,11,21},{5,12,22},{5,13,22},{5,14,22},{5,15,23},{5,16,23},{5,17,23},
//	{6, 9,24},{6,10,24},{6,11,24},{6,12,25},{6,13,25},{6,14,25},{6,15,26},{6,16,26},{6,17,26},
//	{7, 9,24},{7,10,24},{7,11,24},{7,12,25},{7,13,25},{7,14,25},{7,15,26},{7,16,26},{7,17,26},
//	{8, 9,24},{8,10,24},{8,11,24},{8,12,25},{8,13,25},{8,14,25},{8,15,26},{8,16,26},{8,17,26}
//};
////The cell indexes in each of the 9 rows, 9 columns, and 9 squares
//extern const int cellsInGroup[27][9] =
//{
//	{ 0, 1, 2, 3, 4, 5, 6, 7, 8},{ 9,10,11,12,13,14,15,16,17},{18,19,20,21,22,23,24,25,26},
//	{27,28,29,30,31,32,33,34,35},{36,37,38,39,40,41,42,43,44},{45,46,47,48,49,50,51,52,53},
//	{54,55,56,57,58,59,60,61,62},{63,64,65,66,67,68,69,70,71},{72,73,74,75,76,77,78,79,80},
//	{ 0, 9,18,27,36,45,54,63,72},{ 1,10,19,28,37,46,55,64,73},{ 2,11,20,29,38,47,56,65,74},
//	{ 3,12,21,30,39,48,57,66,75},{ 4,13,22,31,40,49,58,67,76},{ 5,14,23,32,41,50,59,68,77},
//	{ 6,15,24,33,42,51,60,69,78},{ 7,16,25,34,43,52,61,70,79},{ 8,17,26,35,44,53,62,71,80},
//	{ 0, 1, 2, 9,10,11,18,19,20},{ 3, 4, 5,12,13,14,21,22,23},{ 6, 7, 8,15,16,17,24,25,26},
//	{27,28,29,36,37,38,45,46,47},{30,31,32,39,40,41,48,49,50},{33,34,35,42,43,44,51,52,53},
//	{54,55,56,63,64,65,72,73,74},{57,58,59,66,67,68,75,76,77},{60,61,62,69,70,71,78,79,80}
//};
//
////6 segments * 9 triplets * 3 cells in triplet
//static const int tripletCells[6][9][3] =
//{
//	{{ 0, 1, 2},{ 3, 4, 5},{ 6, 7, 8},{ 9,10,11},{12,13,14},{15,16,17},{18,19,20},{21,22,23},{24,25,26}},
//	{{27,28,29},{30,31,32},{33,34,35},{36,37,38},{39,40,41},{42,43,44},{45,46,47},{48,49,50},{51,52,53}},
//	{{54,55,56},{57,58,59},{60,61,62},{63,64,65},{66,67,68},{69,70,71},{72,73,74},{75,76,77},{78,79,80}},
//	{{ 0, 9,18},{27,36,45},{54,63,72},{ 1,10,19},{28,37,46},{55,64,73},{ 2,11,20},{29,38,47},{56,65,74}},
//	{{ 3,12,21},{30,39,48},{57,66,75},{ 4,13,22},{31,40,49},{58,67,76},{ 5,14,23},{32,41,50},{59,68,77}},
//	{{ 6,15,24},{33,42,51},{60,69,78},{ 7,16,25},{34,43,52},{61,70,79},{ 8,17,26},{35,44,53},{62,71,80}}
//};
//
//static const int affectedTriplets[9][4] =
//  {{1,2,3,6},{0,2,4,7},{0,1,5,8},{4,5,0,6},{3,5,1,7},{3,4,2,8},{7,8,0,3},{6,8,1,4},{6,7,2,5}};
//
////6 segments * 9 triplets * 12 affected cells
//static const int tripletAffectedCells[6][9][12] =
//{
//	{
//	{ 3, 4, 5, 6, 7, 8, 9,10,11,18,19,20},{ 0, 1, 2, 6, 7, 8,12,13,14,21,22,23},{ 0, 1, 2, 3, 4, 5,15,16,17,24,25,26},
//	{12,13,14,15,16,17, 0, 1, 2,18,19,20},{ 9,10,11,15,16,17, 3, 4, 5,21,22,23},{ 9,10,11,12,13,14, 6, 7, 8,24,25,26},
//	{21,22,23,24,25,26, 0, 1, 2, 9,10,11},{18,19,20,24,25,26, 3, 4, 5,12,13,14},{18,19,20,21,22,23, 6, 7, 8,15,16,17}
//	},{
//	{30,31,32,33,34,35,36,37,38,45,46,47},{27,28,29,33,34,35,39,40,41,48,49,50},{27,28,29,30,31,32,42,43,44,51,52,53},
//	{39,40,41,42,43,44,27,28,29,45,46,47},{36,37,38,42,43,44,30,31,32,48,49,50},{36,37,38,39,40,41,33,34,35,51,52,53},
//	{48,49,50,51,52,53,27,28,29,36,37,38},{45,46,47,51,52,53,30,31,32,39,40,41},{45,46,47,48,49,50,33,34,35,42,43,44}
//	},{
//	{57,58,59,60,61,62,63,64,65,72,73,74},{54,55,56,60,61,62,66,67,68,75,76,77},{54,55,56,57,58,59,69,70,71,78,79,80},
//	{66,67,68,69,70,71,54,55,56,72,73,74},{63,64,65,69,70,71,57,58,59,75,76,77},{63,64,65,66,67,68,60,61,62,78,79,80},
//	{75,76,77,78,79,80,54,55,56,63,64,65},{72,73,74,78,79,80,57,58,59,66,67,68},{72,73,74,75,76,77,60,61,62,69,70,71}
//	},{
//	{27,36,45,54,63,72, 1,10,19, 2,11,20},{ 0, 9,18,54,63,72,28,37,46,29,38,47},{ 0, 9,18,27,36,45,55,64,73,56,65,74},
//	{28,37,46,55,64,73, 0, 9,18, 2,11,20},{ 1,10,19,55,64,73,27,36,45,29,38,47},{ 1,10,19,28,37,46,54,63,72,56,65,74},
//	{29,38,47,56,65,74, 0, 9,18, 1,10,19},{ 2,11,20,56,65,74,27,36,45,28,37,46},{ 2,11,20,29,38,47,54,63,72,55,64,73}
//	},{
//	{30,39,48,57,66,75, 4,13,22, 5,14,23},{ 3,12,21,57,66,75,31,40,49,32,41,50},{ 3,12,21,30,39,48,58,67,76,59,68,77},
//	{31,40,49,58,67,76, 3,12,21, 5,14,23},{ 4,13,22,58,67,76,30,39,48,32,41,50},{ 4,13,22,31,40,49,57,66,75,59,68,77},
//	{32,41,50,59,68,77, 3,12,21, 4,13,22},{ 5,14,23,59,68,77,30,39,48,31,40,49},{ 5,14,23,32,41,50,57,66,75,58,67,76}
//	},{
//	{33,42,51,60,69,78, 7,16,25, 8,17,26},{ 6,15,24,60,69,78,34,43,52,35,44,53},{ 6,15,24,33,42,51,61,70,79,62,71,80},
//	{34,43,52,61,70,79, 6,15,24, 8,17,26},{ 7,16,25,61,70,79,33,42,51,35,44,53},{ 7,16,25,34,43,52,60,69,78,62,71,80},
//	{35,44,53,62,71,80, 6,15,24, 7,16,25},{ 8,17,26,62,71,80,33,42,51,34,43,52},{ 8,17,26,35,44,53,60,69,78,61,70,79}
//	}
//};
//void printVisibleCells() {
//	printf("bm128 visibleCells[81] = {\n");
//	for(int i = 0; i < 81; i++) {
//		bm128 b;
//		b.clear();
//		for(int j = 0; j < 20; j++) {
//			b.setBit(affectedCells[i][j]);
//		}
//		b.setBit(i);
//		b.setBit(96 + affectedGroups[i][0]);
//		b.setBit(96 + affectedGroups[i][1]);
//		b.setBit(96 + affectedGroups[i][2]);
//		bm128toHex(b);
//	}
//	printf("}; //bm128 visibleCells[81]\n");
//}
//
//void printBitsForHouse() {
//	printf("bm128 bitsForHouse[27] = {\n");
//	for(int i = 0; i < 27; i++) {
//		bm128 b;
//		b.clear();
//		for(int j = 0; j < 9; j++) {
//			b.setBit(cellsInGroup[i][j]);
//		}
//		bm128toHex(b);
//	}
//	printf("}; //bm128 bitsForHouse[27]\n");
//}

//void printHouseBits() {
//	printf("const t_128 fsss2::houseBits[27] = { //1 for the 9 cells in the house + 1 in the house marker at 81 + houseindex\n");
//	for(int i = 0; i < 27; i++) {
//		bm128 b;
//		b.clear();
//		for(int j = 0; j < 9; j++) {
//			b.setBit(cellsInGroup[i][j]);
//		}
//		b.setBit(81 + i);
//		bm128toHex(b);
//	}
//	printf("}; //houseBits[27]\n");
//}

//void printTripletMasks() {
//	printf("const t_128 tripletMasks[54] = {\n");
//	for(int s = 0; s < 6; s++) { //band/stack
//		for(int t = 0; t < 9; t++) {//triplet
//			bm128 self;
//			self.clear();
//			bm128 adjacentLine;
//			adjacentLine.clear();
//			bm128 adjacentBox;
//			adjacentBox.clear();
//			for(int c = 0; c < 3; c++) {//cell
//				self.setBit(tripletCells[s][t][c]);
//			}
//			int box = boxByCellIndex[tripletCells[s][t][0]];
//			for(int c = 0; c < 12; c++) {//cell
//				int ac = tripletAffectedCells[s][t][c];
//				if(boxByCellIndex[ac] == box)
//					adjacentBox.setBit(ac);
//				else
//					adjacentLine.setBit(ac);
//			}
//			printf("/t{");
//			bm128toHex(self);
//			bm128toHex(adjacentLine);
//			bm128toHex(adjacentBox);
//			printf("}\n");
//		}
//	}
//	printf("}; //tripletMasks\n");
//}
