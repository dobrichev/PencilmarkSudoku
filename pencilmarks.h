#ifndef PENCILMARKS_H_
#define PENCILMARKS_H_

#include "t_128.h"
#include <iostream>
#include <string>

struct tripletMask {
	t_128 self;
	t_128 adjacentLine;
	t_128 adjacentBox;
};

struct constraints {
	//1 for first 81 bits
	static const t_128 mask81;

	//1 for first 81 bits (cells) and 27 bits from position 96+ (houses)
	static const t_128 mask108;

	//1 for 27 bits at position 96 (houses)
	//static const t_128 mask27;

	//1 for bits to clear when solving particular cell, including the 20 visible cells, self, and the 3 houses at bits 96+
	static const t_128 visibleCells[81];

	//1 for bits in the respective house (9 rows, 9 columns, 9 boxes)
	static const t_128 bitsForHouse[27];

//#ifdef USE_LOCKED_CANDIDATES
	static const tripletMask tripletMasks[54];
//#endif

	//static const uint32_t topCellsHouses; //1 for the houses having cells only within top 64 ones
};

/*
 * Structure for storing and manipulating array of 9 128-bit fields.
 *
 * Used either for allowed digits on each position + flags for solved houses in solver,
 * or for forbidden cell values.
 */
struct pencilmarks {
	bm128 pm[9];
	static const pencilmarks xMask81;
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
	pencilmarks& operator &=(const pencilmarks& other) {
		for(int d = 0; d < 9; d++) {
			pm[d] &= other[d];
		}
		return *this;
	}
	pencilmarks& operator ^=(const pencilmarks& other) {
		for(int d = 0; d < 9; d++) {
			pm[d] ^= other[d];
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
	bool isSubsetOf(const pencilmarks& other) const {
		for(int d = 0; d < 9; d++) {
			if(!pm[d].isSubsetOf(other[d])) return false;
		}
		return true;
	}
	bool isDisjoint(const pencilmarks& other) const {
		for(int d = 0; d < 9; d++) {
			if(!pm[d].isDisjoint(other[d])) return false;
		}
		return true;
	}
	bool isZero() const {
		for(int d = 0; d < 9; d++) {
			if(!pm[d].isZero()) return false;
		}
		return true;
	}
	const bm128& operator[](int digit) const {
		return pm[digit];
	}
	bm128& operator[](int digit) {
		return pm[digit];
	}
	bool operator <(const pencilmarks& other) const {
		for(int d = 0; d < 9; d++) {
			//if(pm[d] < other[d]) return true;
			//if(!(pm[d] == other[d])) return false;
			int diff = pm[d].lge(other[d]);
			if(diff) return diff < 0;
		}
		return false;
	}
	bool operator ==(const pencilmarks& other) const {
		for(int d = 0; d < 9; d++) {
			if(!(pm[d] == other[d])) return false;
		}
		return true;
	}
	void forceCell(int cell, int digit) { //forbid all digits except one
//		for(int d = 0; d < 9; d++) {
//			if(d == digit) continue;
//			pm[digit].setBit(cell);
//		}
		pm[digit].setBit(cell);
	}
	pencilmarks& allowSolution(char* sol) {
		for(int c = 0; c < 81; c++) {
			pm[sol[c] - 1].clearBit(c);
		}
		return *this;
	}
	pencilmarks& fromSolver(const bm128* solverPM) {
		for(int d = 0; d < 9; d++) {
			pm[d] = t_128(constraints::mask81);
			pm[d].clearBits(solverPM[d]); //allow all active pencilmarks
		}
		return *this; //solution pencilmarks must be allowed at some point, see allowSolution(char* sol)
	}
	pencilmarks& fromSolver() {
		for(int d = 0; d < 9; d++) {
			bm128 tmp = t_128(constraints::mask81);
			tmp.clearBits(pm[d]);
			pm[d] = tmp; //allow all active pencilmarks
		}
		return *this; //solution pencilmarks must be allowed at some point, see allowSolution(char* sol)
	}
    void fromList(const char *src) {
    	clear();
    	std::string s(src);
    	std::size_t pos{};
    	while(!s.empty()) {
    		const int i {std::stoi(s, &pos)};
    		if(!pos) break;
    		s = s.substr(pos);
    		if(i < 0 || i > 728) continue;
    		pm[i % 9].setBit(i / 9);
    	}
    }
    bool fromChars81(const char *src) {
    	clear(); //all allowed
    	const char* s = src;
		for(int c = 0; c < 81; c++) {
			//if(*s >= '1' && *s <= '9') forceCell(c, (*s) - '1');
			if(*s >= '1' && *s <= '9') {
				pm[(*s) - '1'].setBit(c);
			}
			else {
				for(int d = 0; d < 9; d++) {
					pm[d].setBit(c);
				}
			}
			s++;
		}
		fromSolver();
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
    friend std::ostream & operator <<(std::ostream& out, const pencilmarks& e) {
    	if(0) {
    		;
    	}
    	else {
        	char buf[730];
        	e.toChars729(buf);
        	out.write(buf, 729);
    	}
    	return out;
    }
    friend std::istream & operator >>(std::istream& in, pencilmarks& e) {
    	char buf[730];
    	//in >> std::setw(729) >> buf;
    	in.read(buf, 729);
    	if(in.good() && in.gcount() == 729) {
    		if(!e.fromChars729(buf)) {
    			in.setstate(std::ios_base::badbit);
    		}
    	}
    	else {
    		e.clear();
    	}
    	return in;
    }
};

#endif // PENCILMARKS_H_
