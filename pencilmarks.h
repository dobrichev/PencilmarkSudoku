#ifndef PENCILMARKS_H_
#define PENCILMARKS_H_

#include "t_128.h"

/*
 * Structure for storing and manipulating array of 9 128-bit fields.
 *
 * Used either for allowed digits on each position + flags for solved houses in solver,
 * or for forbidden cell values.
 */
struct pencilmarks {
	bm128 pm[9];
	void clear() {
		for(int d = 0; d < 9; d++) {
			pm[d].clear();
		}
	}
	void clearBits(const pencilmarks& other) {
		for(int d = 0; d < 9; d++) {
			pm[d].clearBits(other[d]);
		}
	}
	pencilmarks& operator |=(const pencilmarks& other) {
		for(int d = 0; d < 9; d++) {
			pm[d] |= other[d];
		}
		return *this;
	}
	int popcount() const {
		int ret = 0;
		for(int d = 0; d < 9; d++) {
			ret += pm[d].popcount_128();
		}
		return ret;
	}
//	bool isSubsetOf(const pencilmarks& other) const {
//		for(int d = 0; d < 9; d++) {
//			if(!pm[d].isSubsetOf(other[d])) return false;
//		}
//		return true;
//	}
	bool isDisjoint(const pencilmarks& other) const {
		for(int d = 0; d < 9; d++) {
			if(!pm[d].isDisjoint(other[d])) return false;
		}
		return true;
	}
	const bm128& operator[](int digit) const {
		return pm[digit];
	}
	bm128& operator[](int digit) {
		return pm[digit];
	}
	void forceCell(int cell, int digit) { //forbid all digits except one
		for(int d = 0; d < 9; d++) {
			if(d == digit) continue;
			pm[d].setBit(cell);
		}
	}
	pencilmarks& allowSolution(char* sol) {
		for(int c = 0; c < 81; c++) {
			pm[sol[c] - 1].clearBit(c);
		}
		return *this;
	}
	pencilmarks& fromSolver(const bm128* solverPM) {
		for(int d = 0; d < 9; d++) {
			pm[d] = t_128({0xFFFFFFFFFFFFFFFF,    0x0001FFFF});
			pm[d].clearBits(solverPM[d]); //allow all active pencilmarks
		}
		return *this; //solution pencilmarks must be allowed at some point, see allowSolution(char* sol)
	}
	pencilmarks& fromSolver() {
		for(int d = 0; d < 9; d++) {
			bm128 tmp = t_128({0xFFFFFFFFFFFFFFFF,    0x0001FFFF});
			tmp.clearBits(pm[d]);
			pm[d] = tmp; //allow all active pencilmarks
		}
		return *this; //solution pencilmarks must be allowed at some point, see allowSolution(char* sol)
	}
    bool fromChars81(const char *src) {
    	clear(); //all allowed
    	const char* s = src;
		for(int c = 0; c < 81; c++) {
			if(*s >= '1' && *s <= '9') forceCell(c, (*s) - '1');
			s++;
		}
    	return true;
    }
    bool fromChars729(const char *src) {
    	clear();
    	const char* s = src;
		for(int c = 0; c < 81; c++) {
			for(int d = 0; d < 9; d++) {
				if(*s == '.' || *s == '0') pm[d].setBit(c);
				else if(*s != d + '1') return false;
				s++;
			}
		}
    	return true;
    }
    void toChars729(char* dest) const {
    	char* res = dest;
		for(int c = 0; c < 81; c++) {
			for(int d = 0; d < 9; d++) {
				*res = (char)(pm[d].isBitSet(c) ? '.' : d + '1');
				res++;
			}
		}
    }
};
#endif // PENCILMARKS_H_
